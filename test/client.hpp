#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
public:
    Client(int socket);
    int get_socket() const;
    void set_nickname(const std::string& nickname);
    std::string get_nickname() const;
    void set_username(const std::string& username);
    void set_hostname(const std::string& hostname);
    void set_servername(const std::string& servername);
    void set_realname(const std::string& realname);

private:
    int socket;
    std::string nickname;
    std::string username;
    std::string hostname;
    std::string servername;
    std::string realname;
};

#endif // CLIENT_HPP
