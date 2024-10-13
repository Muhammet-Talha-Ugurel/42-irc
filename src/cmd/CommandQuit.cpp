#include "Commands.hpp"

CommandQuit::CommandQuit(std::string msg)
{
		_type = USER;
		this->message = msg;
}

CommandQuit::~CommandQuit() {}

void CommandQuit::execute(const Client *client) { (void)client; }

bool CommandQuit::canExecute(const Client *client)
{
  (void)client;
  return 0;
}
