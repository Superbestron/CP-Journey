// The smart mailer program sends mails to a list of emails provided in a csv file using any SMTP services of your
// choice (eg. smtp.gmail.com or smtp.comp.nus.edu.sg or smtp.nus.edu.sg). The mailer should introduce some delay
// between emails to reduce spam mails. Your mailer should establish an SMTP connection and exchange SMTP messages to
// send mail. You can use any programming language to implement the smart mailer (c, c++, java, python and use any
// high-level API (such as openssl API) to establish connection with the SMTP server.
//
// 1. The mailer should accept an input file (maildata.csv) with list of email ids, names, department codes
// 2. The mailer should accept a department code and send mails only to those departments that are in the list. If the
//    department code is "all" then the mails should be sent to all email ids in the list.
// 3. The mailer should accept subject and body information from a text file. The body should have placeholders which
//    are marked with special characters (such as, #name#, #department#). The placeholders should be replaced by actual
//    names and department names before sending the mail.
// 4. The program print a report showing number of emails sent grouped by department code.
// 5. UI can be GUI or CUI.
// 6. Your codes should be well written and well commented.

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <thread>
#include <vector>

#include <openssl/ssl.h>
#include <openssl/err.h>

struct Recipient {
    std::string email;
    std::string name;
    std::string dept;
};

std::vector<Recipient> load_csv(const std::string& filename) {
    std::vector<Recipient> recipients;
    std::ifstream file(filename);
    std::string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        std::stringstream ss(line);
        Recipient r;
        getline(ss, r.email, ',');
        getline(ss, r.name, ',');
        getline(ss, r.dept, ',');
        recipients.push_back(r);
    }
    return recipients;
}

std::string load_template(const std::string& filename) {
    std::ifstream file(filename);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::string personalize(const std::string& tmpl, const Recipient& r) {
    std::string body = tmpl;
    size_t pos;
    while ((pos = body.find("<NAME>")) != std::string::npos) body.replace(pos, 6, r.name);
    while ((pos = body.find("<DEPT>")) != std::string::npos) body.replace(pos, 6, r.dept);
    return body;
}

// Send a command and get response
bool smtp_cmd(SSL* ssl, const std::string& cmd) {
    SSL_write(ssl, cmd.c_str(), static_cast<int>(cmd.size()));
    char buf[1024];
    int n = SSL_read(ssl, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    std::cout << buf << '\n';
    return (buf[0] == '2' || buf[0] == '3'); // success codes
}

void send_email(const Recipient& r, const std::string& subjectBody, SSL* ssl, const std::string& fromEmail) {
    smtp_cmd(ssl, "MAIL FROM:<" + fromEmail + ">\r\n");
    smtp_cmd(ssl, "RCPT TO:<" + r.email + ">\r\n");
    smtp_cmd(ssl, "DATA\r\n");
    smtp_cmd(ssl, subjectBody + "\r\n.\r\n");
    std::cout << "Sent mail to " << r.email << '\n';
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " <csvfile> <dept|all> <mail.txt> <smtp-server> <from-email>\n";
        return 1;
    }
    std::string csvfile = argv[1];
    std::string dept = argv[2];
    std::string mailfile = argv[3];
    std::string smtp_server = argv[4];
    std::string fromEmail = argv[5];

    auto recipients = load_csv(csvfile);
    auto tmpl = load_template(mailfile);

    // Setup OpenSSL;
    SSL_library_init();
    SSL_load_error_strings();
    const SSL_METHOD* method = TLS_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);

    // Connect to SMTP server (port 465 for SSL)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    addrinfo hints{}, *res;
    memset(&hints, 0, sizeof(hints));

    if (getaddrinfo(smtp_server.c_str(), "465", &hints, &res)) {
        perror("DNS resolution failed");
        return 1;
    }

    sockaddr_in addr = *reinterpret_cast<sockaddr_in*>(res->ai_addr);
    if (connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        perror("connect");
        return 1;
    }

    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return 1;
    }

    smtp_cmd(ssl, "EHLO localhost\r\n");

    std::map<std::string, int> report;

    for (auto& r: recipients) {
        if (dept != "all" && r.dept != dept) continue;
        auto body = personalize(tmpl, r);
        send_email(r, body, ssl, fromEmail);
        report[r.dept]++;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // delay
    }

    smtp_cmd(ssl, "QUIT\r\n");

    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);

    std::cout << "\n=== Report ===\n";
    for (auto&p : report) std::cout << p.first << ": " << p.second << " emails sent\n";

    return 0;
}
