#include "Client.hpp"

#include <cstdlib>
#include <sys/poll.h>

Client::Client(unsigned long _ipv4, unsigned long _port, int p_fd)
    : _ipv4(_ipv4), _port(_port), _poll_fd(p_fd), _nickname(""), _user(0x00)
{
}

Client::~Client() {}

Client::Client(const Client &other)
    : _ipv4(other._ipv4), _port(other._port), _poll_fd(other._poll_fd), _nickname(other._nickname),
      _user(other._user)
{
}

const Client &Client::operator=(const Client &other)
{
  _ipv4     = other._ipv4;
  _port     = other._port;
  _nickname = other._nickname;
  _poll_fd  = other._poll_fd;
  _user     = other._user;
  return *this;
}

bool Client::operator==(const Client &other) const
{
  return _ipv4 == other._ipv4 && _port == other._port;
}

bool Client::operator!=(const Client &other) const
{
  return _ipv4 != other._ipv4 || _port != other._port;
}

bool Client::operator<(const Client &other) const
{
  return _ipv4 < other._ipv4 || _port < other._port;
}

bool Client::operator>(const Client &other) const
{
  return _ipv4 > other._ipv4 || _port > other._port;
}

// TODO: Implement this method correctly
int Client::receiveMessage(const std::string &message) const
{
  (void)message;
  return 0;
}

void Client::flushBuffer() const { memset((void *)_buffer, 0, sizeof(_buffer)); }
