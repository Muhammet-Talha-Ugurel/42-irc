#include "Commands.hpp"

#include <string>

CommandJoin::CommandJoin(vector<std::pair<std::string, std::string> > channelsPasswords)
{
  _type                   = USER;
  this->channelsPasswords = channelsPasswords;
}

CommandJoin::~CommandJoin() {}

void CommandJoin::execute(Client *c, const Server &server)
{
  for (std::vector<std::pair<std::string, std::string> >::iterator it = channelsPasswords.begin();
       it != channelsPasswords.end(); ++it)
  {
    Channel *ch = const_cast<Channel *>(server.getChannelManager()->findChannelByName(it->first));
    if (ch != 0x00)
    {
      if (ch->hasUser(c->getUser()))
      {
        c->receiveMessage(":server 405 " + c->getNickname() + " " + it->first + " :You're already in that channel");
      }
      else if (ch->isInviteOnly() && !ch->hasInvite(c->getUser()))
      {
        c->receiveMessage(":server 473 " + c->getNickname() + " " + it->first + " :You're not invited to this channel");
      }
      else if (ch->isBanned(c->getUser()))
      {
        c->receiveMessage(":server 474 " + c->getNickname() + " " + it->first + " :You're banned from this channel");
      }
      else if (ch->isFull())
      {
        c->receiveMessage(":server 471 " + c->getNickname() + " " + it->first + " :Channel is full");
      }
      else
      {
        if (server.getPasswordManager()->validate(it->second, &ch->getPassword()))
        {
          ch->addUser(c->getUser());
          c->receiveMessage(":" + c->getNickname() + "!" + c->getUser()->getUsername() + "@ JOIN :" + it->first);
          ch->publishMessage(
              ":" + c->getNickname() + "!" + c->getUser()->getUsername() + "@ JOIN :" + it->first, c,
              *server.getClientManager()
          );
        }
        else
        {
          c->receiveMessage(":server 475 " + c->getNickname() + " " + it->first + " :Wrong password");
        }
      }
    }
    else
    {
      Channel channel = Channel(it->first);
      channel.addUser(c->getUser());
      channel.addOperator(c->getUser());
      if (it->second == "")
        channel.setPassword(Password::nan());
      else
        channel.setPassword(server.getPasswordManager()->createPassword(it->second));
      server.getChannelManager()->addChannel(channel);
      c->receiveMessage(":" + c->getNickname() + "!" + c->getUser()->getUsername() + "@ JOIN :" + it->first);
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
