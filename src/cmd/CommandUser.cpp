#include "Commands.hpp"

CommandUser::CommandUser(std::string username, std::string realname)
{
		_type = USER;
		this->username = username;
		this->realname = realname;
}

CommandUser::~CommandUser() {}

void CommandUser::execute(const Client *client) { (void)client; }

bool CommandUser::canExecute(const Client *client)
{
  (void)client;
  return 0;
}
