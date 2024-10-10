#ifndef CLIENT_HPP

#define CLIENT_HPP

#include "../user/User.hpp"

#include <string>

class Client
{
  public:
    Client(unsigned long ipv4, unsigned long ipv6, unsigned long port, const std::string &);
    ~Client();
    Client(const Client &);

    unsigned long      getIpv4() const;
    unsigned long      getIpv6() const;
    unsigned long      getPort() const;

    const std::string &getNickname() const;
    void               setNickname(const std::string &);

    const User        *getUser() const;
    void               setUser(const User *);

    const Client      &operator=(const Client &);
    bool               operator==(const Client &) const;
    bool               operator!=(const Client &) const;
    bool               operator<(const Client &) const;
    bool               operator>(const Client &) const;

    int                receiveMessage(const std::string &) const;

  private:
    Client();
    unsigned long  ipv4;
    unsigned long  ipv6;
    unsigned short port;

    std::string    nickname;
    const User    *user;
};

#endif // !CLIENT_HPP