#include "Commands.hpp"

CommandPass::CommandPass(std::string pass)
{
  _type    = PASS;
  password = pass;
}

CommandPass::~CommandPass() {}

void CommandPass::execute(const Client *client) { (void)client; }

bool CommandPass::canExecute(const Client *client)
{
  (void)client;
  return 0;
}

