#include "Commands.hpp"

CommandPass::CommandPass(Client *client, std::string pass) { 
		_type = PASS;
		_client = client;
		password = pass;
}

CommandPass::~CommandPass() {
}

void CommandPass::execute()
{
}

bool CommandPass::canExecute()
{
		return 0;
}

