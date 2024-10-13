#include "Commands.hpp"

CommandList::CommandList(std::set<std::string> channels) : channels(channels) {}

CommandList::~CommandList() {}

CommandList::CommandList(const CommandList &commandList) { this->channels = commandList.channels; }

void CommandList::execute(const Client *client, const Server &server)
{
  std::set<const Channel *> channels = server.getChannelManager()->getChannelsByIsPublic(true);
}

bool CommandList::canExecute(const Client *client, const Server &server)
{
  if (client->isAuthenticated())
    return true;
  return false;
}