#include "Commands.hpp"

void CommandKick::execute(Client *c, const Server &s)
{
  (void)c;
  Channel    *ch         = s.getChannelManager()->findChannelByName(channel);
  const User *targetUser = s.getUserManager()->findUserByNickname(nickname);

  s.getChannelManager()->removeUserFromChannel(targetUser, ch);
}

bool CommandKick::canExecute(Client *c, const Server &s)
{
  Channel *ch = s.getChannelManager()->findChannelByName(channel);
  if (!ch || (!ch->hasUser(c->getUser()) && (ch->isPrivate() || ch->isSecret()))) {
      c->receiveMessage(":403 " + c->getNickname() + " :No such channel.");
      return false;
    }
  if (ch->hasOperator(c->getUser())) {
      return true;
    }
  c->receiveMessage("482 " + c->getNickname() + " " + channel + " :You're not channel operator");
  return false;
}

void CommandKick::execute(const Client *c, const Server &s) { execute(const_cast<Client *>(c), s); }

bool CommandKick::canExecute(const Client *c, const Server &s)
{
  return canExecute(const_cast<Client *>(c), s);
}
