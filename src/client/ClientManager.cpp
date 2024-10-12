#include "ClientManager.hpp"
#include "../user/UserManager.hpp"
#include "Client.hpp"

#include <stdexcept>

ClientManager::ClientManager() : _clientsByUser(), userManager(&UserManager::getInstance()) {}

ClientManager::~ClientManager() {}

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

      if (user != 0x00) {
          this->_clientsByUser[user] = insertedClient;
        }

      return insertedClient;
    }
  return 0x00;
}

const Client *
ClientManager::updateClientByNickname(const std::string &nickname, const Client &client)
{
  const Client *find = this->findClientByNickname(nickname);
  if (find) {
      Client     *toUpdate = const_cast<Client *>(find);
      const User *oldUser  = toUpdate->getUser();
      const User *newUser  = client.getUser();

      // Update client properties
      toUpdate->setNickname(client.getNickname());
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

void ClientManager::deleteClientByIpv4(const unsigned long ipv4)
{
  const Client *find = this->findClientByIpv4(ipv4);
  if (find) {
      return deleteClient(*find);
    }
  throw std::invalid_argument("Client not found");
}

void ClientManager::deleteClientByIpv6(const unsigned long ipv6)
{
  const Client *find = this->findClientByIpv6(ipv6);
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

const Client *ClientManager::findClientByIpv6(const unsigned long ipv6) const
{
  for (std::set<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
      if (it->getIpv6() == ipv6) {
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

const Client *ClientManager::findClientByPollfd(const pollfd pollfd) const
{
  for (std::map<const struct pollfd, const Client *>::const_iterator it = this->_clientsByPollfd.begin(); it != this->_clientsByPollfd.end(); ++it) {
	  if (it->first.fd == pollfd.fd) {
		  return it->second;
		}
	}
  return 0x00;
}
