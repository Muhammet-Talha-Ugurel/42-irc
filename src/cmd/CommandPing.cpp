#include "Commands.hpp"

CommandPing::CommandPing(std::string server)
{
  _type        = PING;
  this->server = server;
}

CommandPing::~CommandPing() {}

void CommandPing::execute(Client *client, const Server &server)
{
  (void)server;
  client->receiveMessage("PONG " + this->server);
}

bool CommandPing::canExecute(Client *client, const Server &server)
{
		(void)server;
		(void)client;
		return true;
}

void CommandPing::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandPing::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}
