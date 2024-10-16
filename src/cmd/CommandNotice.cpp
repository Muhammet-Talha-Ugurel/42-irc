#include "../Debug.hpp"
#include "Commands.hpp"

CommandNotice::CommandNotice(std::string target, std::string message)
{
  _type         = NOTICE;
  this->target  = target;
  this->message = message;
}

CommandNotice::~CommandNotice() {}

void CommandNotice::execute(Client *client, const Server &server)
{
  Channel *channel = const_cast<Channel *>(server.getChannelManager()->findChannelByName(target));
  if (channel == 0x00)
  {
    if (server.getClientManager()->findClientByNickname(target))
    {
      server.getClientManager()->findClientByNickname(target)->receiveMessage(
          ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ NOTICE " + target + " :" + message
      );
    }
  }
  else
  {
    channel->publishMessage(
        ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ NOTICE " + target + " " + message,
        client, *server.getClientManager()
    );
    DEBUG_LOG("NOTICE sended " << target);
  }
}

bool CommandNotice::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated() == false)
  {
    client->receiveMessage("451 " + client->getNickname() + " :You have not registered");
    return false;
  }
  return true;
}

void CommandNotice::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandNotice::canExecute(const Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return true;
}
