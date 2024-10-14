#include "Commands.hpp"
#include "../user/UserManager.hpp"
#include "../Debug.hpp"

CommandUser::CommandUser(std::string username, std::string realname)
{
		_type = USER;
		this->username = username;
		this->realname = realname;
}

CommandUser::~CommandUser() {}

void CommandUser::execute(Client *client, const Server &server)
{
		const UserManager *userManger = server.getClientManager()->getUserManager();
		if (userManger->findUserByNickname(username))
		{
				client->receiveMessage(":server 433* :Username is already in use\r\n");
				DEBUG_LOG("User name already taken");
		}
		else
		{
				if (client->getUser())
				{
						User *user = (User *)client->getUser();
						user->setUsername(username);
						user->setRealName(realname);
				}
				else
				{
						User user = User();
						user.setUsername(username);
						user.setRealName(realname);
						client->setUser(&user);
				}
				client->receiveMessage(":mtuirc.com 001 " + client->getNickname() + " :Welcome to the Internet Relay Chat Network\r\n");
				DEBUG_LOG("Client username set to " << username);		
		}
		(void)client;
		(void)server;
}

bool CommandUser::canExecute(Client *client, const Server &server)
{
		(void)client;
		(void)server;
		if (client->isAuthenticated()){
			return true;
		}
		return false;
}

void CommandUser::execute(const Client *client, const Server &server)
{
		execute(const_cast<Client *>(client), server);
}

bool CommandUser::canExecute(const Client *client, const Server &server)
{
		return canExecute(const_cast<Client *>(client), server);
}
