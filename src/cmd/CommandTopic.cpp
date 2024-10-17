#include "Commands.hpp"

CommandTopic::CommandTopic(std::string channel, std::string topic) : channel(channel), topic(topic) { _type = TOPIC; }

CommandTopic::~CommandTopic() {}

CommandTopic::CommandTopic(const CommandTopic &commandTopic) : channel(commandTopic.channel), topic(commandTopic.topic)
{
}

void CommandTopic::execute(Client *client, const Server &server)
{
  Channel *ch = server.getChannelManager()->findChannelByName(channel);
  if (ch == 0x00)
  {
    client->receiveMessage(":server 403 " + channel + " :No such channel");
  }
  else
  {
    if (topic.empty())
    {
      if (ch->hasUser(client->getUser()) || !(ch->isPrivate() || ch->isSecret()))
      {
        client->receiveMessage(":" + client->getNickname() + " TOPIC " + channel + " :" + ch->getTopic());
      }
      else
      {
        client->receiveMessage(":server 403 " + channel + " :No such channel");
      }
    }
    else
    {
      if ((ch->isTopicProtected() && ch->hasOperator(client->getUser())) ||
          (!ch->isTopicProtected() && ch->hasUser(client->getUser())))
      {
        ch->setTopic(topic);
        client->receiveMessage(":" + client->getNickname() + " TOPIC " + channel + " :" + topic);
      }
      else
      {
        client->receiveMessage(":server 482 " + channel + " :You're not channel operator");
      }
    }
  }
}

void CommandTopic::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandTopic::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated() == false)
  {
    client->receiveMessage(":server 451 TOPIC :You have not registered");
    return false;
  }
  return true;
}

bool CommandTopic::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
