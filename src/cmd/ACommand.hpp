#ifndef ACOMMAND_HPP

#define ACOMMAND_HPP

#include "../client/Client.hpp"

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
  protected:
    CommandType _type;

  public:
    CommandType  getType() { return _type; };

    virtual void execute(const Client *)    = 0;
    virtual bool canExecute(const Client *) = 0;
};

#endif // !ACOMMAND_HPP
