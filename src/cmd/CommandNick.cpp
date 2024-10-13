#include "Commands.hpp"

CommandNick::CommandNick(std::string nick)
{
  _type    = NICK;
  nickname = nick;
}

CommandNick::~CommandNick() {}

void CommandNick::execute(Client *client, const Server &server)
{
  (void)client;
  (void)server;
}

bool CommandNick::canExecute(Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return 0;
}
