#include "Commands.hpp"

CommandPass::CommandPass(std::string pass)
{
  _type    = PASS;
  password = pass;
}

CommandPass::~CommandPass() {}

void CommandPass::execute(const Client *client, const Server &server)
{
  (void)client;
  (void)server;
}

bool CommandPass::canExecute(const Client *client, const Server &server)
{
  (void)client;
  (void)server;
  return 0;
}
