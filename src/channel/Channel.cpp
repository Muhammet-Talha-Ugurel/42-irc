#include "Channel.hpp"

#include <vector>

Channel::Channel(std::string name)
    : _name(name), _topic(""), _password(Password::nan()), _isPrivate(false)
{
}

Channel::Channel(std::string name, Password password)
    : _name(name), _topic(""), _password(password), _isPrivate(true)
{
}

Channel::Channel(const Channel &channel)
    : _name(channel._name), _topic(channel._topic), _password(channel._password),
      _isPrivate(channel._isPrivate), _users(channel._users), _mods(channel._mods)
{
}

Channel::~Channel() {}

void Channel::addUser(User *user) { _users.insert(user); }

void Channel::removeUser(User *user) { _users.erase(user); }

void Channel::publishMessage(const std::string &message, const ClientManager &clientManager)
{
  std::vector<const Client *> clients = clientManager.findClientsByUsers(_users);

  for (std::vector<const Client *>::const_iterator it = clients.begin(); it != clients.end(); ++it)
  {
      const Client *client = *it;
      if (client) {
          client->receiveMessage(message);
        }
    }
}
