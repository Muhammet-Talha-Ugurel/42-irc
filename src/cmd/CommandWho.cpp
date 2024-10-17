#include "../Debug.hpp"
#include "Commands.hpp"

CommandWho::CommandWho(std::string mask, bool o) : mask(mask), o(o) { _type = WHO; }

CommandWho::~CommandWho() {}

void CommandWho::execute(Client *client, const Server &server)
{
  if (mask == "0")
  {
    std::set<Client> clients = server.getClientManager()->get_clients();
    for (std::set<Client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
      if (it->getNickname() == client->getNickname())
      {
        continue;
      }
      else if (it->getUser()->isVisible() == true)
      {
        continue;
      }
      client->receiveMessage(
          ":mtu 352 " + client->getNickname() + " * " + it->getNickname() + " localhost localhost " +
          it->getUser()->getUsername() + " H :0 " + it->getUser()->getRealName()
      );
      DEBUG_LOG("WHO " << it->getNickname());
    }
  }
  else if (mask[0] == '#')
  {
    DEBUG_LOG("WHO # ");
    Channel *channel = server.getChannelManager()->findChannelByName(mask.substr(1));
    if (channel == 0x00)
    {
      client->receiveMessage(":mtu 403 " + client->getNickname() + " " + mask + " :No such channel");
      return;
    }
    const std::set<const User *> users = channel->getUsers();
    for (std::set<const User *>::iterator it = users.begin(); it != users.end(); ++it)
    {
      if ((*it)->isVisible() == true)
      {
        continue;
      }
      if (client->getNickname() == (*it)->getLastNickname())
      {
        continue;
      }
      client->receiveMessage(
          ":mtu 352 " + client->getNickname() + " " + mask + " " + (*it)->getUsername() + " localhost localhost " +
          (*it)->getLastNickname() + " H :0 " + (*it)->getRealName()
      );
      DEBUG_LOG(
          ":mtu 352 " + client->getNickname() + " " + mask + " " + (*it)->getUsername() + " localhost localhost " +
          (*it)->getLastNickname() + " H :0 " + (*it)->getRealName()
      );
    }
  }
  else
  {
    const Client *result = server.getClientManager()->findClientByNickname(mask);
    if (result == 0x00)
    {
      client->receiveMessage(":mtu 401 " + client->getNickname() + " " + mask + " :No such nick/channel");
      return;
    }
    if (result->getUser()->isVisible() == true)
    {
      return;
    }
    client->receiveMessage(
        ":mtu 352 " + client->getNickname() + mask + result->getNickname() + " localhost localhost " +
        result->getUser()->getUsername() + " H :0 " + result->getUser()->getRealName()
    );
  }
  client->receiveMessage(":mtu 315 " + client->getNickname() + " " + mask + ":End of WHO list");
}

bool CommandWho::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAllowed())
    return true;
  client->receiveMessage(":server 451* :You have not registered");
  return false;
}

void CommandWho::execute(const Client *client, const Server &server) { execute(const_cast<Client *>(client), server); }

bool CommandWho::canExecute(const Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return true;
}
