#include "Commands.hpp"

CommandNick::CommandNick(std::string nick)
{
		_type = NICK;
		this->nickname = nick;
}

CommandNick::~CommandNick() {}

void CommandNick::execute(const Client *client) { (void)client; }

bool CommandNick::canExecute(const Client *client)
{
  (void)client;
  return 0;
}
