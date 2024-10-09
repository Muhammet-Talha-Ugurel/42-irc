#include "ClientManager.hpp"

#include "Client.hpp"

#include <stdexcept>

ClientManager::ClientManager() : userManager(UserManager::getInstance()) {}

ClientManager::~ClientManager() {}

ClientManager &ClientManager::getInstance()
{
  static ClientManager instance;
  return instance;
}

const Client *ClientManager::createClient(const Client &toCreate)
{
  Client toInsert = Client(toCreate);
  this->_clients.insert(toInsert);
  return &(*this->_clients.find(toInsert));
}

const Client *
ClientManager::updateClientByNickname(const std::string &nickname, const Client &client)
{
  const Client *find = this->findClientByNickname(nickname);
  if (find) {
      Client *toUpdate = const_cast<Client *>(find);
      toUpdate->setNickname(client.getNickname());
      toUpdate->setUser(client.getUser());
      return toUpdate;
    }
  return 0x00;
}

void ClientManager::deleteClientByIpv4(const unsigned long ipv4)
{
  const Client *find = this->findClientByIpv4(ipv4);
  if (find) {
      this->_clients.erase(*find);
      return;
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByIpv6(const unsigned long ipv6)
{
  const Client *find = this->findClientByIpv6(ipv6);
  if (find) {
      this->_clients.erase(*find);
      return;
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByPort(const unsigned long port)
{
  const Client *find = this->findClientByPort(port);
  if (find) {
      this->_clients.erase(*find);
      return;
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByNickname(const std::string &nickname)
{
  const Client *find = this->findClientByNickname(nickname);
  if (find) {
      this->_clients.erase(*find);
      return;
    }
  throw std::invalid_argument("Client not found");
}

const Client *ClientManager::findClientByNickname(const std::string &nickname)
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getNickname() == nickname) {
          return &(*it);
        }
    }
  return 0x00;
}

const Client *ClientManager::findClientByIpv4(const unsigned long ipv4)
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getIpv4() == ipv4) {
          return &(*it);
        }
    }
  return 0x00;
}

const Client *ClientManager::findClientByIpv6(const unsigned long ipv6)
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getIpv6() == ipv6) {
          return &(*it);
        }
    }
  return 0x00;
}

const Client *ClientManager::findClientByPort(const unsigned long port)
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getPort() == port) {
          return &(*it);
        }
    }
  return 0x00;
}
