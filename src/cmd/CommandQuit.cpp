#include "Commands.hpp"

CommandQuit::CommandQuit(std::string msg)
{
		_type         = USER;
		this->message = msg;
}

void CommandQuit::execute(Client *client, const Server &server)
{
		std::set<Channel *> channels = server.getChannelManager()->findChannelsByClient(client);
		for (std::set<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
				(*it)->publishMessage(":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ QUIT :" + message, *client, *server.getClientManager());
		server.getClientManager()->deleteClientByNickname(client->getNickname());    
}

bool CommandQuit::canExecute(Client *client, const Server &server)
{
		(void)server;
		return client->isAuthenticated();
}

CommandQuit::~CommandQuit() {}

void CommandQuit::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandQuit::canExecute(const Client *client, const Server &server)
{
		return canExecute(const_cast<Client *>(client), server);
}
