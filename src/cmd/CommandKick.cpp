#include "Commands.hpp"

void CommandKick::execute(Client *c, const Server &s)
{
		(void)c;
		Channel    *ch         = s.getChannelManager()->findChannelByName(channel);
		const Client    *targetClient = s.getClientManager()->findClientByNickname(nickname);
		if (targetClient == NULL) {
				c->receiveMessage(":server 401* " + nickname + " :No such nick/channel");
				return;
		}

		ch->publishMessage(":" + c->getNickname() + " KICK " + ch->getName() + " " + targetClient->getNickname() + " :" + reason, c, *s.getClientManager());
		targetClient->receiveMessage(":" + c->getNickname() + " KICK " + ch->getName() + " " + targetClient->getNickname() + " :" + reason);
		s.getChannelManager()->removeUserFromChannel(targetClient->getUser(), ch);
}

bool CommandKick::canExecute(Client *c, const Server &s)
{
		if (c->isAuthenticated() == false)
		{
				c->receiveMessage("451 " + c->getNickname() + " :You have not registered");
				return false;
		}
		Channel *ch = s.getChannelManager()->findChannelByName(channel);
		if (!ch || (!ch->hasUser(c->getUser()) && (ch->isPrivate() || ch->isSecret())))
		{
				c->receiveMessage(":403 " + c->getNickname() + " :No such channel.");
				return false;
		}
		if (ch->hasOperator(c->getUser()))
		{
				return true;
		}
		c->receiveMessage("482 " + c->getNickname() + " " + channel + " :You're not channel operator");
		return false;
}

void CommandKick::execute(const Client *c, const Server &s) { execute(const_cast<Client *>(c), s); }

bool CommandKick::canExecute(const Client *c, const Server &s) { return canExecute(const_cast<Client *>(c), s); }
