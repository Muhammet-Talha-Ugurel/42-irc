#include "../Debug.hpp"
#include "../user/UserManager.hpp"
#include "Commands.hpp"

CommandPrivmsg::CommandPrivmsg(std::string target, std::string message)
{
		_type    = PRIVMSG;
		this->target = target;
		this->message = message;
}

CommandPrivmsg::~CommandPrivmsg() {}

void CommandPrivmsg::execute(Client *client, const Server &server)
{
		Channel *channel = const_cast<Channel *>(server.getChannelManager()->getChannelByName(target));
		if (channel == 0x00) {
				if (server.getClientManager()->findClientByNickname(target)) {
						server.getClientManager()->findClientByNickname(target)->receiveMessage(
								":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PRIVMSG " + target + " :" + message + "\r\n"
						);
				}
		}
		else {
				channel->publishMessage(":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ PRIVMSG #" + target + " " + message + "\r\n"
, *client, *server.getClientManager());
				DEBUG_LOG("Message published to channel " << target);
		}
		
}

bool CommandPrivmsg::canExecute(Client *client, const Server &server)
{
		(void)server;
		if (client->isAllowed()) {
				return true;
		}
		client->receiveMessage(":server 451* :You have not registered\r\n");
		return false;
}

void CommandPrivmsg::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandPrivmsg::canExecute(const Client *client, const Server &server)
{
		(void)client;
		(void)server;
		return true;
}
