#include "Commands.hpp"

CommandInvite::CommandInvite(std::string invitedNick, std::string channelName)
    : invitedNick(invitedNick), channelName(channelName)
{
  _type = INVITE;
}

CommandInvite::~CommandInvite() {}

void CommandInvite::execute(Client *client, const Server &server)
{
  Channel      *channel = server.getChannelManager()->findChannelByName(channelName);
  const Client *invited = server.getClientManager()->findClientByNickname(invitedNick);
  if (channel != NULL && invited != NULL)
  {
    invited->receiveMessage(":" + client->getNickname() + " INVITE " + invitedNick + " " + channelName);
    channel->inviteUser(invited->getUser());
  }
}

bool CommandInvite::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated())
  {
    Channel *channel = server.getChannelManager()->findChannelByName(channelName);
    if (channel == NULL)
    {
      client->receiveMessage(":server 403* " + channelName + " :No such channel");
      return false;
    }
    else if (channel->hasUser(client->getUser()) == false)
    {
      if (channel->isSecret() || channel->isPrivate())
        client->receiveMessage(":server 403* " + channelName + " :No such channel");
      else
        client->receiveMessage(":server 442* " + channelName + " :You're not on that channel");
      return false;
    }
    else if (server.getClientManager()->findClientByNickname(invitedNick) == NULL)
    {
      client->receiveMessage(":server 401* " + invitedNick + " :No such nick/channel");
      return false;
    }
    else if (channel->hasUser(server.getClientManager()->findClientByNickname(invitedNick)->getUser()))
    {
      client->receiveMessage(":server 443* " + invitedNick + " " + channelName + " :is already on channel");
      return false;
    }
    return true;
  }
  client->receiveMessage(":server 451* :You have not registered");
  return false;
}

void CommandInvite::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandInvite::canExecute(const Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return true;
}
