// Develop a TCP client program using the basic c/c++ socket library to construct a http request and retrieve the file
// “yourip.php” from the url: http://nwtools.atwebpages.com/yourip.php or https version at
// http://varlabs.comp.nus.edu.sg/tools/yourip.php [need to handle encryption]
//
// Parse the contents and display your
// current public IP address from the file returned by the server “varlabs”.
//
// The output should be in the following format: My public IP address is a.b.c.d
// [Note: You should do the assignment by creating the proper HTTP messages as per the RFCs and using basic Socket
// library.]

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <exception>
#include <iostream>
#include <regex>

#include <openssl/ssl.h>
#include <openssl/err.h>

struct Url {
    std::string scheme;
    std::string host;
    std::string path;
    std::string port;
};

Url parse_url(const std::string &u) {
    Url r;
    auto pos = u.find("://");
    if (pos == std::string::npos) throw std::runtime_error("invalid URL");
    r.scheme = u.substr(0, pos);
    std::string rest = u.substr(pos + 3);

    auto slash = rest.find('/');
    std::string hostport = slash == std::string::npos ? rest : rest.substr(0, slash);
    r.path = slash == std::string::npos ? "/" : rest.substr(slash);

    if (auto colon = hostport.find(':'); colon == std::string::npos) {
        r.host = hostport;
        r.port = r.scheme == "https" ? "443" : "80";
    } else {
        r.host = hostport.substr(0, colon);
        r.port = hostport.substr(colon + 1);
    }
    return r;
}

int tcp_connect(const std::string &host, const std::string &port) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    if (const int ec = getaddrinfo(host.c_str(), port.c_str(), &hints, &res); ec != 0)
        throw std::runtime_error(std::string("getaddrinfo: ") + gai_strerror(ec));

    for (auto p = res; p; p = p->ai_next) {
        const int fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fd < 0) continue;
        if (connect(fd, p->ai_addr, p->ai_addrlen) == 0) {
            freeaddrinfo(res);
            return fd;
        }
        close(fd);
    }
    freeaddrinfo(res);
    throw std::runtime_error("connect failed");
}

std::string read_all_http_plain(const int fd) {
    std::string out;
    char buf[1024];
    ssize_t n;
    while ((n = recv(fd, buf, sizeof(buf), 0)) > 0) out.append(buf, n);
    return out;
}

std::string read_all_http_tls(SSL *ssl) {
    std::string out;
    char buf[1024];
    while (true) {
        const int n = SSL_read(ssl, buf, sizeof(buf));
        if (n > 0) {
            out.append(buf, n);
            continue;
        }
        const int err = SSL_get_error(ssl, n);
        if (err == SSL_ERROR_ZERO_RETURN) break; // clean shutdown
        if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE) continue;
        throw std::runtime_error("SSL_read failed");
    }
    return out;
}

std::string extract_body(const std::string &resp, bool &chunked) {
    const auto p = resp.find("\r\n\r\n");
    if (p == std::string::npos) throw std::runtime_error("no header/body separator");
    const std::string headers = resp.substr(0, p);
    std::string body = resp.substr(p + 4);
    // very light check for chunked
    chunked = headers.find("Transfer-Encoding: chunked") != std::string::npos ||
        headers.find("transfer-encoding: chunked") != std::string::npos;
    return body;
}

// Very small chunked decoder (Transfer-Encoding: chunked)
std::string decode_chunked(const std::string &body) {
    std::string out;
    size_t i = 0;
    while (i < body.size()) {
        // read hex chunk size
        const size_t line_end = body.find("\r\n", i);
        if (line_end == std::string::npos) break;
        std::string hex = body.substr(i, line_end - i);
        const size_t chunk = std::stoul(hex, nullptr, 16);
        i = line_end + 2;
        if (chunk == 0) break;
        if (i + chunk > body.size()) throw std::runtime_error("truncated chunk");
        out.append(body, i, chunk);
        i += chunk;
        if (body.compare(i, 2, "\r\n") != 0) throw std::runtime_error("chunk missing CLRF");
        i += 2;
    }
    return out;
}

std::string build_request(const Url &u) {
    std::string req;
    req += "GET " + u.path + " HTTP/1.1\r\n";
    req += "Host: " + u.host + "\r\n";
    req += "User-Agent: ip-client/1.0\r\n";
    req += "Connection: close\r\n";
    req += "\r\n";
    return req;
}

int main(int argc, char *argv[]) {
    try {
        std::string url = argc > 1 ? argv[1] : "https://varlabs.comp.nus.edu.sg/tools/yourip.php";

        Url u = parse_url(url);
        const std::string req = build_request(u);

        std::string response;

        if (u.scheme == "http") {
            int fd = tcp_connect(u.host, u.port);
            if (ssize_t w = send(fd, req.data(), req.size(), 0); w != static_cast<ssize_t>(req.size()))
                throw std::runtime_error("send failed");
            response = read_all_http_plain(fd);
            close(fd);
        } else if (u.scheme == "https") {
            SSL_load_error_strings();
            SSL_library_init();
            const SSL_METHOD *method = TLS_client_method();
            SSL_CTX *ctx = SSL_CTX_new(method);
            if (ctx == nullptr) throw std::runtime_error("SSL_CTX_new failed");

            int fd = tcp_connect(u.host, u.port);
            SSL *ssl = SSL_new(ctx);
            if (ssl == nullptr) throw std::runtime_error("SSL_new failed");
            SSL_set_fd(ssl, fd);
            SSL_set_tlsext_host_name(ssl, u.host.c_str()); // SNI

            if (SSL_connect(ssl) != 1) throw std::runtime_error("SSL_connect failed");

            if (int w = SSL_write(ssl, req.data(), static_cast<int>(req.size())); w <= 0) {
                int err = SSL_get_error(ssl, w);
                std::cerr << "SSL_write error: " << err << "\n";
                throw std::runtime_error("SSL_write failed");
            }

            response = read_all_http_tls(ssl);
            SSL_shutdown(ssl);
            SSL_free(ssl);
            close(fd);
            SSL_CTX_free(ctx);
        } else {
            throw std::runtime_error("unsupported scheme");
        }

        bool chunked = false;
        std::string body = extract_body(response, chunked);
        if (chunked) body = decode_chunked(body);

        // Extract IPv4 (simple regex)
        std::regex ipre(R"((\d{1,3}\.){3}\d{1,3})");
        std::string ip;
        if (std::smatch m; std::regex_search(body, m, ipre)) {
            ip = m.str();
        } else {
            throw std::runtime_error("no IPv4 found in response body");
        }

        std::cout << "My public IP address is " << ip << '\n';
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}
