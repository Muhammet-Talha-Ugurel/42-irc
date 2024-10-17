#include "Commands.hpp"

CommandNames::CommandNames(std::vector<std::string> channels) : channels(channels) { _type = NAMES; }

CommandNames::~CommandNames() {}

void CommandNames::execute(Client *c, const Server &server)
{
  for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
  {
    Channel *ch = server.getChannelManager()->findChannelByName(*it);
    if (ch == 0x00)
    {
      c->receiveMessage(": 403 " + c->getNickname() + " " + *it + " :No such channel");
    }
    else if (false == ch->hasUser(c->getUser()))
    {
      if ((ch->isSecret() || ch->isPrivate()))
      {
        c->receiveMessage(": 403 " + c->getNickname() + " " + *it + " :No such channel");
      }
      else
      {
        c->receiveMessage(": 353 " + c->getNickname() + " = " + *it + " :" + ch->getUserListString());
      }
    }
    else
    {
      if (ch->isPrivate())
      {
        c->receiveMessage(": 353 " + c->getNickname() + " * " + ch->getName() + " :" + ch->getUserListString());
      }
      else if (ch->isSecret())
      {
        c->receiveMessage(": 353 " + c->getNickname() + " @ " + ch->getName() + " :" + ch->getUserListString());
      }
      else
      {
        c->receiveMessage(": 353 " + c->getNickname() + " = " + ch->getName() + " :" + ch->getUserListString());
      }
    }
    c->receiveMessage(": 366 " + c->getNickname() + " " + ch->getName() + " :End of /NAMES list.");
  }
}

void CommandNames::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandNames::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated() == false)
  {
    client->receiveMessage("451 " + client->getNickname() + " :You have not registered");
    return false;
  }
  return true;
}

bool CommandNames::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
