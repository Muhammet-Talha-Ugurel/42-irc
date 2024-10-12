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
  private:
    ACommand();
    CommandType _type;
    Client     *_client;

  public:
    ACommand(CommandType type, Client *client);
    ~ACommand();
    CommandType  getType() { return _type; };

    virtual void execute()                  = 0;
    virtual bool canExecute()               = 0;
    virtual void parse(const std::string &) = 0;
};

#endif // !ACOMMAND_HPP