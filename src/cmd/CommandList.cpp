#include "Commands.hpp"

#define IRC_RPL_LISTSTART "321"
#define IRC_RPL_LIST      "322"
#define IRC_RPL_LISTEND   "323"

CommandList::CommandList(std::set<std::string> channels) : channels(channels) {}

CommandList::~CommandList() {}

CommandList::CommandList(const CommandList &commandList) { this->channels = commandList.channels; }

void CommandList::execute(Client *client, const Server &server)
{
  std::set<const Channel *> channels = server.getChannelManager()->getChannelsByIsPublic(true);

  std::vector<std::string>  names;
  for (std::set<const Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
    names.push_back((*it)->getName());

  (void)client;

  client->receiveMessage(server.respond(IRC_RPL_LISTSTART, client));

  for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); ++it)
    client->receiveMessage(server.respond(IRC_RPL_LIST, client, *it));

  client->receiveMessage(server.respond(IRC_RPL_LISTEND, client));
}

bool CommandList::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated())
    return true;
  return false;
}