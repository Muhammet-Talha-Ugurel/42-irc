#include "ACommand.hpp"
#include "Commands.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

static int parseInt(const string &str)
{
  int i;
  std::istringstream(str) >> i;
  return i;
}

CommandMode::CommandMode(string target, bool add, vector<pair<ModeOperation, string> > modes)
    : target(target), add(add), modes(modes)
{
  _type = MODE;
}

CommandMode::~CommandMode() {}

CommandMode::CommandMode(const CommandMode &other) : target(other.target), modes(other.modes)
{
  _type = other._type;
}

void CommandMode::execute(Client *client, const Server &server)
{
  if (modes.empty())
    execUserModes(client, server);
  else
    execChannelModes(server);
}

bool CommandMode::canExecute(Client *c, const Server &server)
{
	const User *user = c->getUser();
	if (target[0] == '#') {
		Channel *ch = server.getChannelManager()->findChannelByName((target.substr(1)));
		if (!ch) {
			c->receiveMessage("403 " + c->getNickname() + " " + target + " :No such channel");
			return false;
		}
		if (ch->hasOperator(user))
			return true;
		else if (ch->hasUser(user)) {
      if (modes.size() == 1 && modes[0].first == B)
        return true;
			c->receiveMessage("482 " + c->getNickname() + " " + target + " :You're not channel operator");
    }
		else {
      if (ch->isPrivate() || ch->isSecret())
        c->receiveMessage("403 " + c->getNickname() + " " + target + " :No such channel");
      else
        c->receiveMessage("442 " + c->getNickname() + " " + target + " :You're not on that channel");
		}
    return false;
	}
	else {
			if (target == c->getNickname())
				return true;
			c->receiveMessage("502 " + c->getNickname() + " :Cannot change mode for other users");
		}
	return false;
}

void CommandMode::execute(const Client *client, const Server &server)
{
  execute(const_cast<Client *>(client), server);
}

bool CommandMode::canExecute(const Client *client, const Server &server)
{
  return canExecute(const_cast<Client *>(client), server);
}

void CommandMode::execUserModes(Client *c, const Server &server)
{
  (void)server;
  User *user = const_cast<User *>(c->getUser());
  for (vector<pair<ModeOperation, string> >::iterator it = modes.begin(); it != modes.end(); ++it) {
    switch ((*it).first) {
      case I:
        user->setVisible(add ? false : true);
        break;
      default:
        break;
    }
  }
}

void CommandMode::execChannelModes(const Server &server)
{
  Channel *ch = server.getChannelManager()->findChannelByName(target.substr(1));
  for (vector<pair<ModeOperation, string> >::iterator it = modes.begin(); it != modes.end(); ++it) {
    switch ((*it).first) {
      case O:
        if (add)
          ch->addOperator(server.getClientManager()->findClientByNickname((*it).second)->getUser());
        else
          ch->removeOperator(server.getClientManager()->findClientByNickname((*it).second)->getUser());
        break;
      case B:
        if (add)
          ch->banUser(server.getClientManager()->findClientByNickname((*it).second)->getUser());
        else
          ch->unbanUser(server.getClientManager()->findClientByNickname((*it).second)->getUser());
        break;
      case I:
        if (add)
          ch->setInviteOnly(true);
        else
          ch->setInviteOnly(false);
        break;
      case T:
        if (add)
          ch->setTopicProtected(true);
        else
          ch->setTopicProtected(false);
        break;
      case N:
        if (add)
          ch->setNoExternalMessages(true);
        else
          ch->setNoExternalMessages(false);
        break;
      case K:
        if (add)
          ch->setPassword(server.getPasswordManager()->createPassword((*it).second));
        else
          ch->setPassword(Password::nan());
        break;
      case L:
        if (add)
          ch->setUserLimit(parseInt((*it).second));
        else
          ch->setUserLimit(0);
        break;
      default:
        break;
    }
  }  
}

bool getModeOperation(char modeChar, ModeOperation &modeOp)
{
    switch (modeChar)
    {
        case 'o': modeOp = O; break;
        case 'b': modeOp = B; break;
        case 'i': modeOp = I; break;
        case 't': modeOp = T; break;
        case 'n': modeOp = N; break;
        case 'k': modeOp = K; break;
        case 'l': modeOp = L; break;
        case 's': modeOp = S; break;
        default: return false;
    }
    return true;
}

ACommand* CommandMode::parseCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string prefix, cmd, target, modesStr, param;
    std::vector<std::string> params;
    bool add = true;
    std::vector<std::pair<ModeOperation, std::string> > modeList;

    iss >> cmd;

    if (cmd != "MODE")
        return NULL;

    if (!(iss >> target))
        return new Exception("");

    if (!(iss >> modesStr))
        throw std::runtime_error("MODE command missing modes");

    while (iss >> param)
        params.push_back(param);

    size_t paramIndex = 0;
    for (size_t i = 0; i < modesStr.size(); ++i)
    {
        char c = modesStr[i];
        if (c == '+')
        {
            add = true;
            continue;
        }
        else if (c == '-')
        {
            add = false;
            continue;
        }
        else
        {
            ModeOperation modeOp;
            if (!getModeOperation(c, modeOp))
                continue;

            std::string modeParam = "";
            // Modes that require parameters: o, b, k, l
            if (modeOp == O || modeOp == B || modeOp == K || modeOp == L)
            {
                if (paramIndex < params.size())
                {
                    modeParam = params[paramIndex++];
                }
                else
                {
                    // Handle error: Missing parameter for mode
                    continue;
                }
            }
            // Modes that do not require parameters: i, t, n, s
            else
            {
                // No parameter required
            }

            modeList.push_back(std::make_pair(modeOp, modeParam));
        }
    }

    // Create and return CommandMode object
    CommandMode* cmdMode = new CommandMode(target, add, modeList);
    return cmdMode;
}
