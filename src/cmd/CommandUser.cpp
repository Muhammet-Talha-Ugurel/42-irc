#include "../Debug.hpp"
#include "../user/UserManager.hpp"
#include "Commands.hpp"

CommandUser::CommandUser(std::string username, std::string realname)
{
  _type          = USER;
  this->username = username;
  this->realname = realname;
}

CommandUser::~CommandUser() {}

void CommandUser::execute(Client *client, const Server &server)
{
  const UserManager *userManger = server.getUserManager();
  if (userManger->findUserByUsername(username))
  {
    client->receiveMessage(":server 433* :Username is already in use");
    DEBUG_LOG("User name already taken");
  }
  else
  {
    if (client->getUser())
    {
      User *user = (User *)client->getUser();
      user->setUsername(username);
      user->setRealName(realname);
      user->setLastNickname(client->getNickname());
    }
    else
    {
      User user = User();
      user.setUsername(username);
      user.setRealName(realname);
      user.setLastNickname(client->getNickname());
      client->setUser(server.getUserManager()->createUser(user));
    }
    client->receiveMessage(":mtuirc.com 001 " + client->getNickname() + " :Welcome to the Internet Relay Chat Network");
    DEBUG_LOG("Client username set to " << username);
  }
}

bool CommandUser::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAllowed() && client->getNickname() != "")
  {
    return true;
  }
  return false;
}

void CommandUser::execute(const Client *client, const Server &server) { execute(const_cast<Client *>(client), server); }

bool CommandUser::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
