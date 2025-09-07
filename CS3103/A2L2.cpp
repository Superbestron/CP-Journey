// Write a c/c++ program using the basic c/c++ socket library to implement traceroute tool using TCP. The program/tool
// should take destination URL or IP address as input. The tool should send TCP SYN segments to the destination
// successively by increasing IP TTL by 1 each time. Select an appropriate destination port/service based on the
// termination conditions for your program (some of which are stated in point ii below). This will result in
// “host unreachable” or “port unreachable” ICMP error message. Your program should have a RAW socket to retrieve this
// ICMP error message. Your program should output the sender’s IP address of the ICMP error message.

// i.   Prints list set of IP addresses from successive ICMP error messages.
// ii.  Terminates after receiving and printing the IP address from ICMP "port unreachable" or "TCP RST" or
//      "TCP SYN+ACK" messages. If there is no ICMP or TCP RST or "TCP SYN+ACK, the program may terminate after
//      "Time Out" without printing the destination IP. <or> If there is no ICMP or TCP RST, the program may continue
//      with next hop by incrementing the TTL until the TTL value reaches n (n should be decided by you. This is one way
//      to terminate, you can have your own method to terminate the process).
// iii. Checks whether the received ICMP error messages are related to the TCP SYN packets (check only whether the
//      reply is for TCP protocol, no need to check port number).

#include <arpa/inet.h>
#include <cerrno>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <chrono>
#include <random>

#define MAX_TTL 30
#define DEST_PORT 80 // Destination TCP port
#define TIMEOUT_SEC 2

static uint16_t csum16(const void* data, size_t len) {
    uint32_t sum = 0;
    const auto* p = static_cast<const uint16_t*>(data);
    while (len > 1) {
        sum += *p++;
        len -= 2;
    }
    if (len == 1) {
        uint16_t last = 0;
        *reinterpret_cast<uint8_t*>(&last) = *reinterpret_cast<const uint8_t*>(p);
        sum += last;
    }
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return static_cast<uint16_t>(~sum);
}

static in_addr resolve_ipv4(const std::string& host) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET; // IPv4 only for simplicity
    if (int rc = getaddrinfo(host.c_str(), nullptr, &hints, &res); rc != 0) {
        throw std::runtime_error(std::string("getaddrinfo: ") + gai_strerror(rc));
    } else {
        in_addr addr = reinterpret_cast<sockaddr_in*>(res->ai_addr)->sin_addr;
        freeaddrinfo(res);
        return addr;
    }
}

static in_addr get_local_ipv4_for(const in_addr &dst, uint16_t port_hint = 53) {
    // Trick: connect a UDP socket to figure out the chosen local interface/IP
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) throw std::runtime_error("socket UDP failed");
    sockaddr_in peer{};
    peer.sin_family = AF_INET;
    peer.sin_addr = dst;
    peer.sin_port = htons(port_hint);
    if (connect(s, reinterpret_cast<sockaddr*>(&peer), sizeof(peer)) < 0) {
        close(s);
        throw std::runtime_error("connect UDP failed");
    }
    sockaddr_in local{};
    socklen_t len = sizeof(local);
    if (getsockname(s, reinterpret_cast<sockaddr*>(&local), &len) < 0) {
        close(s);
        throw std::runtime_error("getsockname failed");
    }
    close(s);
    return local.sin_addr;
}

static std::string ip_to_str(in_addr a) {
    char buf[INET_ADDRSTRLEN]{};
    inet_ntop(AF_INET, &a, buf, sizeof(buf));
    return buf;
}

#pragma pack(push, 1)
struct PseudoHeader {
    uint32_t src;
    uint32_t dst;
    uint8_t zero;
    uint8_t proto;
    uint16_t tcp_len;
};
#pragma pack(pop)

static void build_syn_packet(uint8_t* buf, size_t& pkt_len, in_addr src, in_addr dst, uint16_t sport, uint16_t dport,
                             uint8_t ttl, uint32_t seq_seed) {
    // IP header + TCP header (no options)
    auto* iph = reinterpret_cast<ip*>(buf);
    auto* tcph = reinterpret_cast<tcphdr*>(buf + sizeof(ip));

    memset(buf, 0, sizeof(ip) + sizeof(tcphdr));

    // IP
    iph->ip_v = 4;
    iph->ip_hl = 5; // 20 bytes
    iph->ip_tos = 0;
    iph->ip_len = htons(sizeof(ip) + sizeof(tcphdr));
    iph->ip_id = htons(static_cast<uint16_t>(0x123 ^ ttl)); // arbitrary
    iph->ip_off = 0;
    iph->ip_ttl = ttl;
    iph->ip_p = IPPROTO_TCP;
    iph->ip_src.s_addr = src.s_addr;
    iph->ip_dst.s_addr = dst.s_addr;
    iph->ip_sum = 0;
    iph->ip_sum = csum16(iph, sizeof(ip));

    // TCP
    tcph->th_sport = htons(sport);
    tcph->th_dport = htons(dport);
    // Put TTL into the high byte of seq so we can correlate
    tcph->th_seq = htonl((static_cast<uint32_t>(ttl) << 24) | (seq_seed & 0x00FFFFFF));
    tcph->th_ack = 0;
    tcph->th_off = 5; // 20 bytes
    tcph->th_flags = TH_SYN;
    tcph->th_win = htons(65535);
    tcph->th_sum = 0;
    tcph->th_urp = 0;

    // TCP checksum (pseudo-header)
    PseudoHeader ph{};
    ph.src = iph->ip_src.s_addr;
    ph.dst = iph->ip_dst.s_addr;
    ph.zero = 0;
    ph.proto = IPPROTO_TCP;
    ph.tcp_len = htons(sizeof(tcphdr));

    // Temporary buffer used just for checksum calculation
    uint8_t csum_buf[sizeof(PseudoHeader) + sizeof(tcphdr)];
    memcpy(csum_buf, &ph, sizeof(PseudoHeader));
    memcpy(csum_buf + sizeof(PseudoHeader), tcph, sizeof(tcphdr));
    tcph->th_sum = csum16(csum_buf, sizeof(csum_buf));

    pkt_len = sizeof(ip) + sizeof(tcphdr);
}

enum HopResult {
    HR_NONE,
    HR_TIME_EXCEEDED,     // got ICMP Time Exceeded (print hop)
    HR_DEST_PORT_UNREACH, // got ICMP Port Unreachable (print hop, terminate)
    HR_TCP_RST,           // got TCP RST from dest (print hop, terminate)
    HR_TCP_SYNACK,        // got TCP SYN+ACK from dest (print hop, terminate)
};

struct RecvOutcome {
    HopResult result = HR_NONE;
    in_addr sender{}; // address to print (ICMP/TCP sender)
};

std::string hopresult_to_str(HopResult r) {
    switch (r) {
        case HR_NONE: return "NONE";
        case HR_TIME_EXCEEDED: return "ICMP Time Exceeded";
        case HR_DEST_PORT_UNREACH: return "ICMP Port Unreachable";
        case HR_TCP_RST: return "TCP RST";
        case HR_TCP_SYNACK: return "TCP SYN+ACK";
        default: return "Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, const RecvOutcome& o) {
    os << "[sender=" << ip_to_str(o.sender) << ", result=" << hopresult_to_str(o.result) << "]";
    return os;
}

// Parse ICMP message and check if it refers to our TCP probe
static bool parse_icmp_related_to_tcp(const uint8_t* buf, ssize_t len, RecvOutcome& out, const in_addr& src_me,
                                      const in_addr& dst_target) {
    if (len < static_cast<ssize_t>(sizeof(ip))) return false;

    const ip* iphdr = reinterpret_cast<const ip*>(buf);
    size_t ip_hl = iphdr->ip_hl * 4; // There might be options field populated
    if (len < static_cast<ssize_t>(ip_hl) + static_cast<ssize_t>(sizeof(icmp))) return false;

    const icmp* icmphdr = reinterpret_cast<const icmp*>(buf + ip_hl);

    // We only care about ICMP error msgs that embed our original IP header
    if (!(icmphdr->icmp_type == ICMP_TIMXCEED || icmphdr->icmp_type == ICMP_UNREACH)) return false;

    const uint8_t* embed = buf + ip_hl + sizeof(icmp);
    ssize_t embed_len = static_cast<size_t>(len) - (ip_hl + static_cast<ssize_t>(sizeof(icmp)));
    if (embed_len < static_cast<ssize_t>(sizeof(ip))) return false;

    const ip* orig_ip = reinterpret_cast<const ip*>(embed);
    // Assignment says: only check protocol==TCP (no need to check ports)
    if (orig_ip->ip_p != IPPROTO_TCP) return false;

    // (Optional but safe) also verify it matches our addresses
    if (orig_ip->ip_src.s_addr != src_me.s_addr || orig_ip->ip_dst.s_addr != dst_target.s_addr) return false;

    out.sender.s_addr = iphdr->ip_src.s_addr;

    if (icmphdr->icmp_type == ICMP_TIMXCEED) {
        out.result = HR_TIME_EXCEEDED;
        return true;
    }

    if (icmphdr->icmp_type == ICMP_UNREACH) {
        // Code 3 = Port unreachable
        if (icmphdr->icmp_code == ICMP_UNREACH_PORT) {
            out.result = HR_DEST_PORT_UNREACH;
            return true;
        } else {
            // Other dest-unreach codes; still a hop to print, but not terminate
            out.result = HR_TIME_EXCEEDED;
            return true;
        }
    }
    return false;
}

static bool parse_tcp_from_dest(const uint8_t* buf, ssize_t len, RecvOutcome& out, const in_addr& src_me,
                                const in_addr& dst_target, uint16_t my_sport, uint16_t dst_dport) {
    if (len < static_cast<ssize_t>(sizeof(ip))) return false;
    const ip* iphdr = reinterpret_cast<const ip*>(buf);
    size_t ip_hl = iphdr->ip_hl * 4;
    if (iphdr->ip_p != IPPROTO_TCP) return false;
    if (len < static_cast<ssize_t>(ip_hl) + static_cast<ssize_t>(sizeof(tcphdr))) return false;

    const auto* tcp = reinterpret_cast<const tcphdr*>(buf + ip_hl);

    // We expect a response from destination to us:
    if (iphdr->ip_src.s_addr != dst_target.s_addr) return false; // from dest
    if (iphdr->ip_dst.s_addr != src_me.s_addr) return false;     // to us
    if (ntohs(tcp->th_dport) != my_sport) return false;          // to our source port
    if (ntohs(tcp->th_sport) != dst_dport) return false;         // from dest port

    out.sender.s_addr = iphdr->ip_src.s_addr;
    if (tcp->th_flags & TH_RST) {
        out.result = HR_TCP_RST;
        return true;
    } else if (tcp->th_flags & TH_SYN && tcp->th_flags & TH_ACK) {
        out.result = HR_TCP_SYNACK;
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: sudo " << argv[0] << " <dest-host-or-ip> [port=80] [maxTTL=30] [timeout_ms=2000]\n";
            return 2;
        }
        std::string dest_str = argv[1];
        uint16_t dport = (argc >= 3) ? static_cast<uint16_t>(std::stoi(argv[2])) : 80;
        int max_ttl = (argc >= 4) ? std::stoi(argv[3]) : 30;
        int timeout_ms = (argc >= 5) ? std::stoi(argv[4]) : 2000;

        in_addr dst = resolve_ipv4(dest_str);
        in_addr src = get_local_ipv4_for(dst);

        // Random-ish source port
        std::mt19937 rng{std::random_device{}()};
        auto sport = uint16_t(49152 + (rng() % 16384)); // ephemeral range
        uint32_t seq_seed = rng();

        // Raw socket for sending IP packets with custom header
        int send_sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
        if (send_sock < 0) {
            perror("socket send (raw tcp)");
            return 1;
        }
        int one = 1;
        if (setsockopt(send_sock, IPPROTO_IP, IP_TTL, &one, sizeof(one)) < 0) {
            perror("setsockopt IP_HDRINCL");
            return 1;
        }

        // Raw socket for ICMP receiving
        int icmp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        if (icmp_sock < 0) {
            perror("socket icmp");
            return 1;
        }

        // Raw socket for TCP receiving
        int tcp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
        if (tcp_sock < 0) {
            perror("socket tcp raw recv");
            return 1;
        }

        std::cout << "Tracing route to " << dest_str << " [" << ip_to_str(dst) << "] over TCP port " << dport << '\n';

        sockaddr_in dst_sa{};
        dst_sa.sin_family = AF_INET;
        dst_sa.sin_addr = dst;
        dst_sa.sin_port = htons(dport); // not used by raw IP sendto, but fine

        const size_t MAX_PKT = 1500;
        uint8_t pkt[MAX_PKT];

        for (int ttl = 1; ttl <= max_ttl; ttl++) {
            // Build SYN with specific TTL
            size_t pkt_len = 0;
            build_syn_packet(pkt, pkt_len, src, dst, sport, dport, static_cast<uint8_t>(ttl), seq_seed);

            // Send
            std::cout << "Sending to " << ip_to_str(dst) << " TTL=" << ttl << " pkt_len=" << pkt_len << '\n';
            ssize_t sent = sendto(send_sock, pkt, pkt_len, 0, reinterpret_cast<sockaddr*>(&dst_sa), sizeof(dst_sa));
            if (sent < 0 || static_cast<size_t>(sent) != pkt_len) {
                perror("sendto");
                std::cout << "*1\n";
                continue;
            }

            // Wait for either ICMP or TCP response
            auto t_start = std::chrono::steady_clock::now();
            bool printed = false;

            while (true) {
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - t_start).count();
                if (elapsed >= timeout_ms) break;

                fd_set rdfs;
                FD_ZERO(&rdfs);
                FD_SET(icmp_sock, &rdfs);
                FD_SET(tcp_sock, &rdfs);
                int maxfd = std::max(icmp_sock, tcp_sock);

                timeval tv{};
                tv.tv_sec = (timeout_ms - static_cast<int>(elapsed)) / 1000;
                tv.tv_usec = ((timeout_ms - static_cast<int>(elapsed)) % 1000) * 1000;

                int r = select(maxfd + 1, &rdfs, nullptr, nullptr, &tv);
                if (r < 0) {
                    if (errno == EINTR) continue;
                    perror("select");
                    break;
                } else if (r == 0) continue;

                uint8_t buf[1024];
                sockaddr_in from{};
                socklen_t fromlen = sizeof(from);

                if (FD_ISSET(icmp_sock, &rdfs)) {
                    ssize_t n = recvfrom(icmp_sock, buf, sizeof(buf), 0, reinterpret_cast<sockaddr*>(&from), &fromlen);

                    if (n > 0) {
                        RecvOutcome o{};
                        if (parse_icmp_related_to_tcp(buf, n, o, src, dst)) {
                            // Print hop IP (sender of the ICMP)
                            std::cout << o << '\n';
                            printed = true;
                            if (o.result == HR_DEST_PORT_UNREACH) {
                                // Terminate on Port Unreachable
                                return 0;
                            }
                            // For Time Exceeded or other dest-unreach codes, go to next TTL
                            break;
                        }
                    }
                }

                if (FD_ISSET(tcp_sock, &rdfs)) {
                    ssize_t n = recvfrom(tcp_sock, buf, sizeof(buf), 0, reinterpret_cast<sockaddr*>(&from), &fromlen);
                    if (n > 0) {
                        RecvOutcome o{};
                        if (parse_tcp_from_dest(buf, n, o, src, dst, sport, dport)) {
                            // Destination reached
                            std::cout << o << '\n';
                            if (o.result == HR_TCP_RST || o.result == HR_TCP_SYNACK) {
                                return 0;
                            }
                        }
                    }
                }
            }

            if (!printed) {
                std::cout << ttl << " *\n";
            }
            std::cout << '\n';
        }

        // Reached max TTL without termination condition
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}
