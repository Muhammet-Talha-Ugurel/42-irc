#include "Commands.hpp"

CommandPrivmsg::CommandPrivmsg(std::string target, std::string message)
{
  _type         = PRIVMSG;
  this->target  = target;
  this->message = message;
}

CommandPrivmsg::~CommandPrivmsg() {}

void CommandPrivmsg::execute(Client *client, const Server &server)
{
  if (target[0] == '#')
  {
    Channel *channel = const_cast<Channel *>(server.getChannelManager()->findChannelByName(target));
    if (!channel)
    {
      client->receiveMessage(":server 403 " + client->getNickname() + " " + target + " :No such channel");
    }
    else
    {
      if (channel->isBanned(client->getUser()))
      {
        client->receiveMessage(":server 474 " + client->getNickname() + " " + target + " :Cannot send to channel");
      }
      else if (channel->hasUser(client->getUser()))
      {
        channel->publishMessage(
            ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PRIVMSG " + target + " " +
                message,
            client, *server.getClientManager()
        );
      }
      else if (channel->isNoExternalMessages())
      {
        if (channel->isPrivate() || channel->isSecret())
        {
          client->receiveMessage(":server 403 " + client->getNickname() + " " + target + " :No such channel");
        }
        else
        {
          client->receiveMessage(":server 404 " + client->getNickname() + " " + target + " :Cannot send to channel");
        }
      }
    }
  }
  else
  {
    if (server.getClientManager()->findClientByNickname(target))
    {
      server.getClientManager()->findClientByNickname(target)->receiveMessage(
          ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PRIVMSG " + target + " :" + message
      );
    }
    else
    {
      client->receiveMessage(":server 401 " + client->getNickname() + " " + target + " :No such nick/channel");
    }
  }
}

bool CommandPrivmsg::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated())
    return true;
  client->receiveMessage(":server 451* :You have not registered");
  return false;
}

void CommandPrivmsg::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandPrivmsg::canExecute(const Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return true;
}
