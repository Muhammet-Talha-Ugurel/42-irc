#ifndef CLIENT_HPP

#define CLIENT_HPP

#include "user/User.hpp"

#include <cstdint>

class Client
{
  public:
    Client();
	Client(Client &);
    ~Client();

  private:
    uint64_t ipv4;
    uint64_t ipv6;
    User    *logged_user;
};

#endif // !CLIENT_HPP