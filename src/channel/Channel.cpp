#include "Channel.hpp"

#include <sstream>
#include <vector>

Channel::Channel(std::string name) : _topic("No topic is set"), _password(Password::nan()), _isPrivate(false)
{
  if (name[0] != '#')
  {
    _name = "#" + name;
  }
  else
  {
    _name = name;
  }
}

Channel::Channel(std::string name, Password password) : _topic(""), _password(password), _isPrivate(true)
{
  if (name[0] != '#')
  {
    _name = "#" + name;
  }
  else
  {
    _name = name;
  }
}

Channel::Channel(const Channel &channel)
    : _name(channel._name), _topic(channel._topic), _password(channel._password), _isPrivate(channel._isPrivate),
      _users(channel._users), _oprs(channel._oprs)
{
}

void Channel::publishMessage(const std::string &message, const Client &sender, const ClientManager &clientManager)
{
  std::vector<const Client *> clients = clientManager.findClientsByUsers(_users);

  for (std::vector<const Client *>::const_iterator it = clients.begin(); it != clients.end(); ++it)
  {
    if ((*it) && (*it) != &sender)
    {
      (*it)->receiveMessage(message);
    }
  }
}

void Channel::addUser(const User *user)
{
  _users.insert(user);
  if (_users.size() == 1)
  {
    _oprs.insert(user);
  }
  _invited.erase(user);
}

void Channel::removeUser(const User *user)
{
  _users.erase(user);
  _oprs.erase(user);
}

void Channel::banUser(const User *user)
{
  _banned.insert(user);
  removeUser(user);
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
  for (std::set<const User *>::iterator it = _users.begin(); it != _users.end(); ++it)
  {
    ss << (hasOperator(*it) ? "@" : "") << (*it)->getLastNickname() << " ";
  }
  return ss.str();
}
