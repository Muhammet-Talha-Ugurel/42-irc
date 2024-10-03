#ifndef CLIENT_HPP

#define CLIENT_HPP

#include "User.hpp"

class Client
{
  public:
    Client(const Client &);
    ~Client();
    Client(unsigned long ipv4, unsigned long ipv6, unsigned long port);

    void     setUserData(User *);
    User    *getUserData() noexcept;

    unsigned long getIpv4() noexcept;
    unsigned long getIpv6() noexcept;
    unsigned long getPort() noexcept;

  private:
    Client();
    unsigned long       ipv4;
    unsigned long       ipv6;
    unsigned short port;

    User          *logged_user;
};

#endif // !CLIENT_HPP