#ifndef CLIENT_HPP

#define CLIENT_HPP

#include "../user/User.hpp"

#include <cstring>
#include <string>
#include <sys/poll.h>

class Client
{
  public:
    Client(unsigned long ipv4, unsigned long port, int p_fd);
    ~Client();
    Client(const Client &);

    unsigned long      getIpv4() const { return _ipv4; }
    unsigned long      getPort() const { return _port; }

    const std::string &getNickname() const { return _nickname; }
    void               setNickname(const std::string &n) { _nickname = n; }

    const User        *getUser() const { return _user; }
    void               setUser(const User *user) { _user = user; };

    const char        *getBuffer() const { return _buffer; }
    void               flushBuffer() const;

    int                getPollFd() const { return _poll_fd; }
    void               setPollFd(int p_fd) { _poll_fd = p_fd; }

    const Client      &operator=(const Client &);
    bool               operator==(const Client &) const;
    bool               operator!=(const Client &) const;
    bool               operator<(const Client &) const;
    bool               operator>(const Client &) const;

    int                receiveMessage(const std::string &) const;

    void               allow() { _allowed = true; };
    bool               isAllowed() const { return _allowed; }

    bool               isAuthenticated() const { return isAllowed() && _nickname != "" && _user != 0x00; }

  private:
    Client();
    unsigned long  _ipv4;
    unsigned short _port;
    int            _poll_fd;
    char           _buffer[1024];
    bool           _allowed;

    std::string    _nickname;
    const User    *_user;
};

namespace std
{
template <> struct less<class Client>
{
    bool operator()(const Client &lhs, const Client &rhs) const { return lhs < rhs; }
};
} // namespace std

#endif // !CLIENT_HPP
