#include "Commands.hpp"

CommandJoin::CommandJoin(std::vector<std::string> channels, std::vector<std::string> keys)
{
		_type = USER;
		this->keys = keys;
		this->channels = channels;
}

CommandJoin::~CommandJoin() {}

void CommandJoin::execute(const Client *client) { (void)client; }

bool CommandJoin::canExecute(const Client *client)
{
  (void)client;
  return 0;
}
