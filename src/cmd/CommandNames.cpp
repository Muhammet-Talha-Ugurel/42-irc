#include "Commands.hpp"

CommandNames::CommandNames(std::vector<std::string> channels) : channels(channels) { _type = NAMES; }

CommandNames::~CommandNames() {}

void CommandNames::execute(Client *client, const Server &server)
{
  for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
  {
    Channel    *ch = server.getChannelManager()->findChannelByName(*it);
    std::string msg;
    if (false == ch->hasUser(client->getUser()))
    {
      if ((ch->isSecret() || ch->isPrivate()))
      {
        msg = ": 403 " + client->getNickname() + " " + *it + " :No such channel";
      }
      else
      {
        msg = ": 353 " + client->getNickname() + " = " + *it + " :" + ch->getUserListString();
      }
    }
    else
    {
      if (ch->isPrivate())
      {
        msg = ": 353 " + client->getNickname() + " * #" + ch->getName() + " :" + ch->getUserListString();
      }
      else if (ch->isSecret())
      {
        msg = ": 353 " + client->getNickname() + " @ #" + ch->getName() + " :" + ch->getUserListString();
      }
      else
      {
        msg = ": 353 " + client->getNickname() + " = #" + ch->getName() + " :" + ch->getUserListString();
      }
    }
    client->receiveMessage(msg);
    client->receiveMessage(": 366 " + client->getNickname() + " #" + ch->getName() + " :End of /NAMES list.");
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
