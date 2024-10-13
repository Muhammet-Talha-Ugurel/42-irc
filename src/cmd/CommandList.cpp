#include "Commands.hpp"

CommandList::CommandList(std::set<std::string> channels) : channels(channels) {}

CommandList::~CommandList() {}

CommandList::CommandList(const CommandList &commandList) { this->channels = commandList.channels; }

void CommandList::execute(Client *client, const Server &server)
{
  std::set<const Channel *> channels = server.getChannelManager()->getChannelsByIsPublic(true);

  (void)client;
  std::vector<std::string> names;
  for (std::set<const Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
    names.push_back((*it)->getName());
}

bool CommandList::canExecute(Client *client, const Server &server)
{
  (void)server;
  if (client->isAuthenticated())
    return true;
  return false;
}