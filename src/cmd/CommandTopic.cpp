#include "Commands.hpp"

CommandTopic::CommandTopic(std::string channel, std::string topic) : channel(channel), topic(topic)
{
  _type = TOPIC;
}

CommandTopic::~CommandTopic() {}

CommandTopic::CommandTopic(const CommandTopic &commandTopic)
    : channel(commandTopic.channel), topic(commandTopic.topic)
{
}

void CommandTopic::execute(Client *client, const Server &server)
{
  Channel *ch = server.getChannelManager()->findChannelByName(channel);
  if (ch == 0x00) {
      return;
    }
  ch->setTopic(topic);
  server.respond("332", client, ch->getName() + " :" + topic);
}

void CommandTopic::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandTopic::canExecute(Client *client, const Server &server)
{
  if (client->isAuthenticated() == false) {
      client->receiveMessage(":server 451 TOPIC :You have not registered");
      return false;
    }

  Channel *ch = server.getChannelManager()->findChannelByName(channel);
  if (ch == 0x00)
    client->receiveMessage(":server 403 " + channel + " :No such channel");
  else if (ch->hasUser(client->getUser()) == false)
    client->receiveMessage(":server 442 " + channel + " :You're not on that channel");
  else if (ch->hasOperator(client->getUser()) == false)
    client->receiveMessage(":server 482 " + channel + " :You're not a channel operator");
  else
    return true;
  return false;
}

bool CommandTopic::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
