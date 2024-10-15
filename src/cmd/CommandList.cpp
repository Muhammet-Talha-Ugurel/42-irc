#include "Commands.hpp"

#define IRC_RPL_LISTSTART "321"
#define IRC_RPL_LIST      "322"
#define IRC_RPL_LISTEND   "323"

CommandList::CommandList(std::set<std::string> channels) : channels(channels) {}

CommandList::~CommandList() {}

CommandList::CommandList(const CommandList &commandList) { this->channels = commandList.channels; }

void CommandList::execute(Client *client, const Server &server)
{
  std::set<const Channel *> channels = server.getChannelManager()->findChannelsByIsPublic(true);

  client->receiveMessage(server.respond(IRC_RPL_LISTSTART, client));
  for (std::set<const Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
    client->receiveMessage(server.respond(
        IRC_RPL_LIST, client, "#" + (*it)->getName() + " " + (*it)->getUserCountString() + " :" + (*it)->getTopic()
    ));

  (void)client;

  client->receiveMessage(server.respond(IRC_RPL_LISTEND, client));
}

bool CommandList::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated())
    return true;
  return false;
}

void CommandList::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandList::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
