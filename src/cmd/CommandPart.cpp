#include "Commands.hpp"
#include "../Debug.hpp"

CommandPart::CommandPart(std::vector<std::string> channels, std::string message) : channels(channels), message(message)
{
		_type = PART;
}

void CommandPart::execute(Client *client, const Server &server)
{
		std::set<Channel *> channels = server.getChannelManager()->getChannelsByClient(client);
		for (std::set<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it) {
				for (std::vector<std::string>::iterator it2 = this->channels.begin(); it2 != this->channels.end(); ++it2) {
						if ((*it)->getName() == *it2) {
								(*it)->publishMessage(":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PART #" + (*it)->getName() + " :" + message + "\r\n", *client, *server.getClientManager());
								client->receiveMessage(":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PART #" + (*it)->getName() + " :" + message + "\r\n");
								(*it)->removeUser(client->getUser());
								DEBUG_LOG("User " << client->getNickname() << " has left channel " << (*it)->getName());
						}
				}
		}
}

bool CommandPart::canExecute(Client *client, const Server &server)
{
		(void)server;
		return client->isAuthenticated();
}

CommandPart::~CommandPart() {}

void CommandPart::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandPart::canExecute(const Client *client, const Server &server)
{
		return canExecute(const_cast<Client *>(client), server);
}
