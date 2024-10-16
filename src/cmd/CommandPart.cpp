#include "../Debug.hpp"
#include "Commands.hpp"

CommandPart::CommandPart(vector<string> channels, string message) : channels(channels), message(message)
{
  _type = PART;
}

void CommandPart::execute(Client *client, const Server &server)
{

  for (vector<string>::iterator it = this->channels.begin(); it != this->channels.end(); ++it)
  {
    Channel *ch = server.getChannelManager()->findChannelByName(*it);
    if (ch == 0x00)
    {
      client->receiveMessage(": 403 " + client->getNickname() + " " + ch->getName() + " :No such channel");
      continue;
    }
    if (false == ch->hasUser(client->getUser()))
    {
      if ((ch->isSecret() || ch->isPrivate()))
      {
        client->receiveMessage(": 403 " + client->getNickname() + " " + ch->getName() + " :No such channel");
      }
      else
      {
        client->receiveMessage(": 442 " + client->getNickname() + " " + ch->getName() + " :You're not on that channel");
      }
    }
    else
    {
      ch->publishMessage(
          ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PART " + ch->getName() + " :" +
              message,
          client, *server.getClientManager()
      );
      client->receiveMessage(
          ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PART " + ch->getName() + " :" +
          message
      );
      server.getChannelManager()->removeUserFromChannel(client->getUser(), ch);
      DEBUG_LOG("User " << client->getNickname() << " has left channel " << ch->getName());
    }
  }
}

bool CommandPart::canExecute(Client *client, const Server &server)
{
  (void)server;
  return client->isAuthenticated();
}

CommandPart::~CommandPart() {}

void CommandPart::execute(const Client *client, const Server &server) { execute(const_cast<Client *>(client), server); }

bool CommandPart::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
