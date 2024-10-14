#include "Commands.hpp"
#include "../Debug.hpp"
#include <iostream>

CommandPass::CommandPass(std::string pass)
{
		_type    = PASS;
		password = pass;
}

CommandPass::~CommandPass() {}

void CommandPass::execute(Client *client, const Server &server)
{
		if (server.getPasswordManager()->validate(password, &server.getPassword())) {
				server.getClientManager()->allowClient(client);
				DEBUG_LOG("Client allowed.");	
		} else {
				DEBUG_LOG("Client not allowed.");	
				client->receiveMessage(":server 464* : Incorrect Password\r\n");
		}
}

bool CommandPass::canExecute(Client *client, const Server &server)
{
		(void)client;
		(void)server;
		return true;
}

void CommandPass::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandPass::canExecute(const Client *client, const Server &server)
{
		(void)client;
		(void)server;
		return true;
}
