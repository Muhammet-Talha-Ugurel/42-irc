#include "Commands.hpp"

CommandCap::CommandCap()
{
  _type    = CAP;
}

CommandCap::~CommandCap() {}

void CommandCap::execute(Client *client, const Server &server)
{
		(void)server;
		client->receiveMessage(":server CAP * LS :");
}

bool CommandCap::canExecute(Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return true;
}

void CommandCap::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandCap::canExecute(const Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return true;
}
