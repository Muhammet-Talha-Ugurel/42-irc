#include "../Debug.hpp"
#include "Commands.hpp"

#include <string>

CommandJoin::CommandJoin(std::vector<std::string> channels, std::vector<std::string> keys)
{
  _type          = USER;
  this->keys     = keys;
  this->channels = channels;
}

CommandJoin::~CommandJoin() {}

void CommandJoin::execute(Client *client, const Server &server)
{
  std::vector<std::string>::iterator it = channels.begin();
  while (it != channels.end()) {
      Channel *ptr = const_cast<Channel *>(server.getChannelManager()->getChannelByName(*it));
      if (ptr != 0x00) {
          ptr->addUser((User *)client->getUser());
          std::cout << "<" << client->getNickname() << ">" << std::endl;
          std::cout << "<" << client->getUser()->getUsername() << ">" << std::endl;
          client->receiveMessage(
              ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ JOIN :#" +
              *it + "\r\n"
          );
        }
      else {
          Channel channel = Channel(*it);
          channel.addUser((User *)client->getUser());
          server.getChannelManager()->addChannel(channel);
          client->receiveMessage(
              ":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ JOIN :#" +
              *it + "\r\n"
          );
        }
      it++;
    }
}

bool CommandJoin::canExecute(Client *client, const Server &server)
{
  (void)client;
  (void)server;
  if (client->isAuthenticated()) {
      return true;
    }
  return false;
}

void CommandJoin::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandJoin::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
