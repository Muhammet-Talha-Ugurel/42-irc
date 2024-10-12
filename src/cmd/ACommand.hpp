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
    Client     *_client;

  public:
    CommandType  getType() { return _type; };

    virtual void execute()                  = 0;
    virtual bool canExecute()               = 0;
};

#endif // !ACOMMAND_HPP
