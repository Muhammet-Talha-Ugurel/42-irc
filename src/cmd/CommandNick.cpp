#include "Commands.hpp"
#include "../Debug.hpp"

CommandNick::CommandNick(std::string nick)
{
		_type    = NICK;
		nickname = nick;
}

CommandNick::~CommandNick() {}

void CommandNick::execute(Client *client, const Server &server)
{
		if (server.getClientManager()->findClientByNickname(nickname))
		{
				client->receiveMessage(":server 433* :Nickname is already in use\r\n");
		}
		else
		{
				client->setNickname(nickname);
				DEBUG_LOG("Client nickname set to " << nickname);
		}
}

bool CommandNick::canExecute(Client *client, const Server &server)
{
		(void)client;
		(void)server;
		if (client->isAuthenticated()){
			return true;
		}
		return false;
}

void CommandNick::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandNick::canExecute(const Client *client, const Server &server)
{
		return canExecute(const_cast<Client *>(client), server);
}
