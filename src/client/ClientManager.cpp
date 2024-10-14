#include "ClientManager.hpp"

#include "../user/UserManager.hpp"
#include "Client.hpp"

#include <stdexcept>
#include <sys/poll.h>

ClientManager::ClientManager() : _clientsByUser(), userManager(&UserManager::getInstance()) {}

ClientManager::~ClientManager() {}

const UserManager *ClientManager::getUserManager() { return userManager; }

ClientManager::ClientManager(const ClientManager &other)
{
  this->_clients    = other._clients;
  this->userManager = other.userManager;
}

ClientManager &ClientManager::operator=(const ClientManager &other)
{
  this->_clients    = other._clients;
  this->userManager = other.userManager;
  return *this;
}

void ClientManager::deleteClient(const Client &toDelete)
{
  const User *user = toDelete.getUser();

  if (user != 0x00) {
      userManager->deleteUser(*user);
      this->_clientsByUser.erase(user);
    }
  this->_clients.erase(toDelete);
}

ClientManager &ClientManager::getInstance()
{
  static ClientManager instance;
  return instance;
}

const Client *ClientManager::createClient(const Client &toCreate)
{
  Client                                      toInsert = Client(toCreate);
  std::pair<std::set<Client>::iterator, bool> result   = this->_clients.insert(toInsert);

  if (result.second) {
      const Client *insertedClient = &(*result.first);
      const User   *user           = insertedClient->getUser();

      int           pfd            = insertedClient->getPollFd();
      this->_clientsByFd[pfd]      = insertedClient;

      if (user != 0x00) {
          this->_clientsByUser[user] = insertedClient;
        }

      return insertedClient;
    }
  return 0x00;
}

const Client *ClientManager::findClientByNickname(const std::string &nickname) const
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getNickname() == nickname) {
          return &(*it);
        }
    }
  return 0x00;
}

const Client *ClientManager::findClientByIpv4(const unsigned long ipv4) const
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getIpv4() == ipv4) {
          return &(*it);
        }
    }
  return 0x00;
}

const Client *ClientManager::findClientByPort(const unsigned long port) const
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getPort() == port) {
          return &(*it);
        }
    }
  return 0x00;
}

const Client *ClientManager::findClientByUser(const User *user) const
{
  std::map<const User *, const Client *>::const_iterator it = this->_clientsByUser.find(user);
  if (it != this->_clientsByUser.end()) {
      return it->second;
    }
  return 0x00;
}

const Client *ClientManager::findClientByPollfd(const pollfd pollfd) const
{
  for (std::map<const int, const Client *>::const_iterator it = this->_clientsByFd.begin();
       it != this->_clientsByFd.end(); ++it)
    {
      if (it->first == pollfd.fd) {
          return it->second;
        }
    }
  return 0x00;
}

const std::vector<const Client *>
ClientManager::findClientsByUsers(const std::set<const User *> &users) const
{
  std::vector<const Client *> result;

  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (users.find(it->getUser()) != users.end()) {
          result.push_back(&(*it));
        }
    }
  return result;
}

const Client *ClientManager::updateClient(const Client *find, const Client &src)
{
  if (find) {
      Client     *toUpdate = const_cast<Client *>(find);
      const User *oldUser  = toUpdate->getUser();
      const User *newUser  = src.getUser();

      // Update client properties
      toUpdate->setNickname(src.getNickname());
      toUpdate->setUser(newUser);

      // Update the _clientsByUser map if the user has changed
      if (oldUser != newUser) {
          if (oldUser != 0x00) {
              this->_clientsByUser.erase(oldUser);
            }
          if (newUser != 0x00) {
              this->_clientsByUser[newUser] = toUpdate;
            }
        }

      return toUpdate;
    }
  return 0x00;
}

const Client *ClientManager::updateClientByNickname(const std::string &nickname, const Client &src)
{
  return updateClient(this->findClientByNickname(nickname), src);
}

const Client *ClientManager::updateClientByIpv4(const unsigned long ipv4, const Client &src)
{
  return updateClient(this->findClientByIpv4(ipv4), src);
}

const Client *ClientManager::updateClientByPort(const unsigned long port, const Client &src)
{
  return updateClient(this->findClientByPort(port), src);
}

const Client *ClientManager::updateClientByUser(const User *user, const Client &src)
{
  return updateClient(this->findClientByUser(user), src);
}

const Client *ClientManager::updateClientByPollfd(const pollfd pollfd, const Client &src)
{
  return updateClient(this->findClientByPollfd(pollfd), src);
}

void ClientManager::deleteClientByIpv4(const unsigned long ipv4)
{
  const Client *find = this->findClientByIpv4(ipv4);
  if (find) {
      return deleteClient(*find);
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByPort(const unsigned long port)
{
  const Client *find = this->findClientByPort(port);
  if (find) {
      return deleteClient(*find);
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByNickname(const std::string &nickname)
{
  const Client *find = this->findClientByNickname(nickname);
  if (find) {
      return deleteClient(*find);
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByUser(const User *user)
{
  const Client *find = this->findClientByUser(user);
  if (find) {
      return deleteClient(*find);
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByPollfd(const pollfd pollfd)
{
  const Client *find = this->findClientByPollfd(pollfd);
  if (find) {
      return deleteClient(*find);
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::allowClient(const Client *client)
{
  if (client) {
      const_cast<Client *>(client)->setAllowed(true);
    }
}
