#include "Commands.hpp"

#include <string>

CommandJoin::CommandJoin(std::vector<std::string> channels, std::vector<std::string> keys)
{
  _type          = USER;
  this->keys     = keys;
  this->channels = channels;
}

CommandJoin::~CommandJoin() {}

void CommandJoin::execute(Client *c, const Server &server)
{
  for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
  {
    Channel *ch = const_cast<Channel *>(server.getChannelManager()->findChannelByName(*it));
    if (ch != 0x00)
    {
      if (ch->hasUser(c->getUser()))
      {
        c->receiveMessage(":server 405 " + c->getNickname() + " " + *it + " :You're already in that channel");
      }
      else if (ch->isInviteOnly() && !ch->hasInvite(c->getUser()))
      {
        c->receiveMessage(":server 473 " + c->getNickname() + " " + *it + " :You're not invited to this channel");
      }
      else if (ch->isBanned(c->getUser()))
      {
        c->receiveMessage(":server 474 " + c->getNickname() + " " + *it + " :You're banned from this channel");
      }
      else if (ch->isFull())
      {
        c->receiveMessage(":server 471 " + c->getNickname() + " " + *it + " :Channel is full");
      }
      else
      {
        ch->addUser(c->getUser());
        c->receiveMessage(":" + c->getNickname() + "!" + c->getUser()->getUsername() + "@ JOIN :" + *it);
        ch->publishMessage(
            ":" + c->getNickname() + "!" + c->getUser()->getUsername() + "@ JOIN :" + *it, *c,
            *server.getClientManager()
        );
      }
    }
    else
    {
      Channel channel = Channel(*it);
      channel.addUser(c->getUser());
      channel.addOperator(c->getUser());
      server.getChannelManager()->addChannel(channel);
      c->receiveMessage(":" + c->getNickname() + "!" + c->getUser()->getUsername() + "@ JOIN :" + *it);
    }
  }
}

bool CommandJoin::canExecute(Client *client, const Server &server)
{
  (void)server;
if (client->isAuthenticated() == false)
  {
    client->receiveMessage("451 " + client->getNickname() + " :You have not registered");
    return false;
  }
  return true;
}

void CommandJoin::execute(const Client *client, const Server &server) { execute(const_cast<Client *>(client), server); }

bool CommandJoin::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
