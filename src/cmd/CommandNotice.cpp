#include "../Debug.hpp"
#include "Commands.hpp"

CommandNotice::CommandNotice(std::string target, std::string message)
{
		_type    = NOTICE;
		this->target = target;
		this->message = message;
}

CommandNotice::~CommandNotice() {}

void CommandNotice::execute(Client *client, const Server &server)
{
		Channel *channel = const_cast<Channel *>(server.getChannelManager()->findChannelByName(target));
		if (channel == 0x00) {
				if (server.getClientManager()->findClientByNickname(target)) {
						server.getClientManager()->findClientByNickname(target)->receiveMessage(
								":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ NOTICE #" + target + " :" + message + "\r\n"
						);
				}
		}
		else {
				channel->publishMessage(":" + client->getNickname() + "!" + client->getUser()->getUsername() + "@ NOTICE #" + target + " " + message + "\r\n"
, *client, *server.getClientManager());
				DEBUG_LOG("NOTICE sended " << target);
		}
		
}

bool CommandNotice::canExecute(Client *client, const Server &server)
{
		(void)server;
		if (client->isAllowed()) {
				return true;
		}
		client->receiveMessage(":server 451* :You have not registered\r\n");
		return false;
}

void CommandNotice::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandNotice::canExecute(const Client *client, const Server &server)
{
		(void)client;
		(void)server;
		return true;
}
