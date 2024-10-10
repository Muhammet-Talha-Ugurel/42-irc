#include "Client.hpp"

#include <iostream>

Client::Client(
    unsigned long ipv4, unsigned long ipv6, unsigned long port, const std::string &nickname
)
    : ipv4(ipv4), ipv6(ipv6), port(port), nickname(nickname)
{
}

Client::~Client() {}

Client::Client(const Client &other)
{
  ipv4     = other.ipv4;
  ipv6     = other.ipv6;
  port     = other.port;
  nickname = other.nickname;
  user     = other.user;
}

unsigned long      Client::getIpv4() const { return ipv4; }

unsigned long      Client::getIpv6() const { return ipv6; }

unsigned long      Client::getPort() const { return port; }

const std::string &Client::getNickname() const { return nickname; }

void               Client::setNickname(const std::string &nickname) { this->nickname = nickname; }

const User        *Client::getUser() const { return user; }

void               Client::setUser(const User *user) { this->user = user; }

const Client      &Client::operator=(const Client &other)
{
  ipv4     = other.ipv4;
  ipv6     = other.ipv6;
  port     = other.port;
  nickname = other.nickname;
  user     = other.user;
  return *this;
}

bool Client::operator==(const Client &other) const
{
  return ipv4 == other.ipv4 && ipv6 == other.ipv6 && port == other.port;
}

bool Client::operator!=(const Client &other) const
{
  return ipv4 != other.ipv4 || ipv6 != other.ipv6 || port != other.port;
}

bool Client::operator<(const Client &other) const
{
  return ipv4 < other.ipv4 || ipv6 < other.ipv6 || port < other.port;
}

bool Client::operator>(const Client &other) const
{
  return ipv4 > other.ipv4 || ipv6 > other.ipv6 || port > other.port;
}

// TODO: Implement this method correctly
int Client::receiveMessage(const std::string &message) const
{
  std::cout << "Received message: " << message << std::endl;
  return 0;
}
