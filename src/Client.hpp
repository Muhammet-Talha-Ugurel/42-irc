#ifndef CLIENT_HPP

#define CLIENT_HPP

#include "User.hpp"

#include <cstdint>

class Client
{
  public:
    Client(const Client &);
    ~Client();
    Client(uint64_t ipv4, uint64_t ipv6, uint64_t port);

    void     setUserData(User *);
    User    *getUserData() noexcept;

    uint64_t getIpv4() noexcept;
    uint64_t getIpv6() noexcept;
    uint64_t getPort() noexcept;

  private:
    Client();
    uint64_t       ipv4;
    uint64_t       ipv6;
    unsigned short port;

    User          *logged_user;
};

#endif // !CLIENT_HPP