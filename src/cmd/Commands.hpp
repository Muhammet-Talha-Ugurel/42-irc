#ifndef COMMANDS_HPP
#pragma once

#include "ACommand.hpp"

class CommandPass : public ACommand
{
  public:
    CommandPass(User *user) : ACommand(PASS, user) {};
    ~CommandPass();
    CommandPass(const CommandPass &commandPass);

    void execute();
    bool canExecute();
};

class CommandNick : public ACommand
{
  public:
    CommandNick(User *user) : ACommand(NICK, user) {};
    ~CommandNick();
    CommandNick(const CommandNick &commandNick);

    void execute();
    bool canExecute();
};

class CommandUser : public ACommand
{
  private:
    
  public:
    CommandUser(User *user) : ACommand(USER, user) {};
    ~CommandUser();
    CommandUser(const CommandUser &commandUser);

    void execute();
    bool canExecute();
};

class CommandQuit : public ACommand
{
  public:
    CommandQuit(User *user) : ACommand(QUIT, user) {};
    ~CommandQuit();
    CommandQuit(const CommandQuit &commandQuit);

    void execute();
    bool canExecute();
};

class CommandJoin : public ACommand
{
  public:
    CommandJoin(User *user) : ACommand(JOIN, user) {};
    ~CommandJoin();
    CommandJoin(const CommandJoin &commandJoin);

    void execute();
    bool canExecute();
};

class CommandCap : public ACommand
{
  public:
    CommandCap(User *user) : ACommand(CAP, user) {};
    ~CommandCap();
    CommandCap(const CommandCap &commandCap);

    void execute();
    bool canExecute();
};

class CommandPing : public ACommand
{
  public:
    CommandPing(User *user) : ACommand(PING, user) {};
    ~CommandPing();
    CommandPing(const CommandPing &commandPing);

    void execute();
    bool canExecute();
};

class CommandMode : public ACommand
{
  public:
    CommandMode(User *user) : ACommand(MODE, user) {};
    ~CommandMode();
    CommandMode(const CommandMode &commandMode);

    void execute();
    bool canExecute();
};

class CommandWho : public ACommand
{
  public:
    CommandWho(User *user) : ACommand(WHO, user) {};
    ~CommandWho();
    CommandWho(const CommandWho &commandWho);

    void execute();
    bool canExecute();
};

class CommandPrivmsg : public ACommand
{
  public:
    CommandPrivmsg(User *user) : ACommand(PRIVMSG, user) {};
    ~CommandPrivmsg();
    CommandPrivmsg(const CommandPrivmsg &commandPrivmsg);

    void execute();
    bool canExecute();
};

class CommandNotice : public ACommand
{
  public:
    CommandNotice(User *user) : ACommand(NOTICE, user) {};
    ~CommandNotice();
    CommandNotice(const CommandNotice &commandNotice);

    void execute();
    bool canExecute();
};

class CommandKick : public ACommand
{
  public:
    CommandKick(User *user) : ACommand(KICK, user) {};
    ~CommandKick();
    CommandKick(const CommandKick &commandKick);

    void execute();
    bool canExecute();
};

class CommandPart : public ACommand
{
  public:
    CommandPart(User *user) : ACommand(PART, user) {};
    ~CommandPart();
    CommandPart(const CommandPart &commandPart);

    void execute();
    bool canExecute();
};

class CommandTopic : public ACommand
{
  public:
    CommandTopic(User *user) : ACommand(TOPIC, user) {};
    ~CommandTopic();
    CommandTopic(const CommandTopic &commandTopic);

    void execute();
    bool canExecute();
};

class CommandNames : public ACommand
{
  public:
    CommandNames(User *user) : ACommand(NAMES, user) {};
    ~CommandNames();
    CommandNames(const CommandNames &commandNames);

    void execute();
    bool canExecute();
};

class CommandList : public ACommand
{
  public:
    CommandList(User *user) : ACommand(LIST, user) {};
    ~CommandList();
    CommandList(const CommandList &commandList);

    void execute();
    bool canExecute();
};

class CommandDcc : public ACommand
{
  public:
    CommandDcc(User *user) : ACommand(DCC, user) {};
    ~CommandDcc();
    CommandDcc(const CommandDcc &commandDcc);

    void execute();
    bool canExecute();
};

#endif // !COMMANDS_HPP