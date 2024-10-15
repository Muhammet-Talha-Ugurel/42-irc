#include "Channel.hpp"

#include <sstream>
#include <vector>

Channel::Channel(std::string name)
    : _name(name), _topic("No topic is set"), _password(Password::nan()), _isPrivate(false)
{
}

Channel::Channel(std::string name, Password password)
    : _name(name), _topic(""), _password(password), _isPrivate(true)
{
}

Channel::Channel(const Channel &channel)
    : _name(channel._name), _topic(channel._topic), _password(channel._password),
      _isPrivate(channel._isPrivate), _users(channel._users), _oprs(channel._oprs)
{
}

void Channel::publishMessage(
    const std::string &message, const Client &sender, const ClientManager &clientManager
)
{
  std::vector<const Client *> clients = clientManager.findClientsByUsers(_users);

  for (std::vector<const Client *>::const_iterator it = clients.begin(); it != clients.end(); ++it)
  {
      if ((*it) && (*it) != &sender) {
          (*it)->receiveMessage(message);
        }
    }
}

std::string Channel::getUserCountString() const
{
  std::stringstream ss;
  ss << _users.size();
  return ss.str();
}

std::string Channel::getOperatorCountString() const
{
  std::stringstream ss;
  ss << _oprs.size();
  return ss.str();
}

std::string Channel::getUserListString()
{
  std::stringstream ss;
  for (std::set<const User *>::iterator it = _users.begin(); it != _users.end(); ++it) {
      ss << (hasOperator(*it) ? "@" : "") << (*it)->getLastNickname() << " ";
    }
  return ss.str();
}
