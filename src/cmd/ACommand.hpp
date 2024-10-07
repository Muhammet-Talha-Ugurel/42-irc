#ifndef ACOMMAND_HPP

#define ACOMMAND_HPP

#include "../user/User.hpp"

enum CommandType
{
  PASS,
  NICK,
  USER,
  QUIT,
  JOIN,
  CAP,
  PING,
  MODE,
  WHO,
  PRIVMSG,
  NOTICE,
  KICK,
  PART,
  TOPIC,
  NAMES,
  LIST,
  DCC
};

class ACommand
{
  private:
    ACommand();
    CommandType _type;
    User       *_user;

  public:
    ACommand(CommandType type, User *user);
    ~ACommand();
    CommandType  getType() { return _type; };

    virtual void execute()    = 0;
    virtual bool canExecute() = 0;
};

#endif // !ACOMMAND_HPP