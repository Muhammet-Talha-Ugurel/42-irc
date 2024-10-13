#include "Commands.hpp"

CommandPass::CommandPass(std::string pass)
{
  _type    = PASS;
  password = pass;
}

CommandPass::~CommandPass() {}

void CommandPass::execute(Client *client, const Server &server)
{
  if (server.getPasswordManager()->validate(password, server.getPassword())) {
      client->allow();
    }
}

bool CommandPass::canExecute(Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return true;
}
