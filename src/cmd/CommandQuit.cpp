#include "Commands.hpp"

CommandQuit::CommandQuit(std::string msg)
{
  _type         = USER;
  this->message = msg;
}

void CommandQuit::execute(Client *client, const Server &server)
{
  (void)server;
  (void)client;
}

bool CommandQuit::canExecute(Client *client, const Server &server)
{
  (void)client;
  return 0;
}

CommandQuit::~CommandQuit() {}

void CommandQuit::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandQuit::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
