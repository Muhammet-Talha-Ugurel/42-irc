#include "Channel.hpp"

#include <ctime>
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

void Channel::publishMessage(const std::string &message, Client *sender, const ClientManager &clientManager)
{
  std::vector<const Client *> clients = clientManager.findClientsByUsers(_users);

  for (std::vector<const Client *>::const_iterator it = clients.begin(); it != clients.end(); ++it)
  {
    if ((*it) && (*it) != sender)
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

void Channel::addBanMask(std::string banner, std::string mask)
{
  Ban ban(banner, mask, time(NULL));
  _banned.insert(ban);
}

void Channel::removeBanMask(std::string mask)
{
  for (std::set<Ban>::iterator it = _banned.begin(); it != _banned.end(); ++it)
  {
    if ((*it).getMask() == mask)
    {
      _banned.erase(it);
      return;
    }
  }
}

std::set<User *> Channel::findUsersByMask(const std::string &mask) const
{
  std::set<User *> users;
  for (std::set<const User *>::iterator it = _users.begin(); it != _users.end(); ++it)
  {
    if ((*it)->getLastNickname() == mask.substr(0, mask.find("!")) &&
        (*it)->getUsername() == mask.substr(mask.find("!") + 1, mask.find("@") - mask.find("!") - 1))
    {
      users.insert(const_cast<User *>(*it));
    }
  }
  return users;
}

Ban Channel::findBanMask(const std::string &mask) const
{
  for (std::set<Ban>::iterator it = _banned.begin(); it != _banned.end(); ++it)
  {
    if ((*it).getMask() == mask)
    {
      return *it;
    }
  }
  return Ban();
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

bool Channel::isBanned(const User *user) const
{
  for (std::set<Ban>::iterator it = _banned.begin(); it != _banned.end(); ++it)
  {
    if (evalMask((*it).getMask(), user))
    {
      return true;
    }
  }
  return false;
}

bool Channel::evalMask(const std::string &mask, const User *user) const
{
  if (mask.find("!") == std::string::npos || mask.find("@") == std::string::npos)
  {
    return false;
  }

  std::string nick     = mask.substr(0, mask.find("!"));
  std::string username = mask.substr(mask.find("!") + 1, mask.find("@") - mask.find("!") - 1);

  return (user->getUsername() == username && (user->getLastNickname() == nick || nick == "*")) ||
         (user->getLastNickname() == nick && (user->getUsername() == username || username == "*")) || mask == "*!*@*";
}
