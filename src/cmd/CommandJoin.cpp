#include "Commands.hpp"
#include "../Debug.hpp"
#include <string>

CommandJoin::CommandJoin(std::vector<std::string> channels, std::vector<std::string> keys)
{
  _type          = USER;
  this->keys     = keys;
  this->channels = channels;
}

CommandJoin::~CommandJoin() {}

void CommandJoin::execute(Client *client, const Server &server)
{		
		std::vector<std::string>::iterator it = channels.begin();
		while (it != channels.end())
		{
				if (server.getChannelManager()->getChannelByName(*it)) {
						Channel *channel = (Channel *)server.getChannelManager()->getChannelByName(*it);
						channel->addUser((User *)client->getUser());
						client->receiveMessage(":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ JOIN :#" + *it + "\r\n");
				}
				else {
						Channel channel = Channel(*it);
						channel.addUser((User *)client->getUser());
						server.getChannelManager()->addChannel(channel);
						client->receiveMessage(":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ JOIN :#" + *it + "\r\n");
				}
				it++;
		}
}

bool CommandJoin::canExecute(Client *client, const Server &server)
{
		(void)client;
		(void)server;
		if (client->isAuthenticated()){
			return true;
		}
		return false;
}

void CommandJoin::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandJoin::canExecute(const Client *client, const Server &server)
{
		return canExecute(const_cast<Client *>(client), server);
}
