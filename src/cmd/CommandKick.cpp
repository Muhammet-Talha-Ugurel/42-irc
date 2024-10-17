#include "Commands.hpp"

void CommandKick::execute(Client *c, const Server &s)
{
		(void)c;
		for (std::vector<std::string>::iterator chit = channels.begin(); chit != channels.end(); ++chit)
		{
				Channel *ch = s.getChannelManager()->findChannelByName(*chit);
				if (!ch || (!ch->hasUser(c->getUser()) && (ch->isPrivate() || ch->isSecret())))
				{
						c->receiveMessage(":403 " + c->getNickname() + " :No such channel.");
				}
				if (ch->hasOperator(c->getUser()))
				{
						for (std::vector<std::string>::iterator nit = nicknames.begin(); nit != nicknames.end(); ++nit)
						{
								const Client    *targetClient = s.getClientManager()->findClientByNickname(*nit);
								if (targetClient == NULL) {
										c->receiveMessage(":server 401* " + *nit + " :No such nick/channel");
										return;
								}
								ch->publishMessage(":" + c->getNickname() + " KICK " + ch->getName() + " " + targetClient->getNickname() + " :" + reason, c, *s.getClientManager());
								c->receiveMessage(":" + c->getNickname() + " KICK " + ch->getName() + " " + targetClient->getNickname() + " :" + reason);
								s.getChannelManager()->removeUserFromChannel(targetClient->getUser(), ch);
						}
				}
				else
						c->receiveMessage("482 " + c->getNickname() + " " + *chit + " :You're not channel operator");
		}
}

bool CommandKick::canExecute(Client *c, const Server &s)
{
		(void)s;
		if (c->isAuthenticated() == false)
		{
				c->receiveMessage("451 " + c->getNickname() + " :You have not registered");
				return false;
		}
		return true;
}

void CommandKick::execute(const Client *c, const Server &s) { execute(const_cast<Client *>(c), s); }

bool CommandKick::canExecute(const Client *c, const Server &s) { return canExecute(const_cast<Client *>(c), s); }
