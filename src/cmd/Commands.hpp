#include <list>
#include <string>
#include <utility>
#include <vector>

#ifndef COMMANDS_HPP
#pragma once

#include "../Server.hpp"
#include "ACommand.hpp"

class CommandPass : public ACommand
{
  private:
    std::string password;

  public:
    CommandPass(std::string);
    ~CommandPass();
    CommandPass(const CommandPass &);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandNick : public ACommand
{
  private:
    std::string nickname;

  public:
    CommandNick(std::string);
    ~CommandNick();
    CommandNick(const CommandNick &commandNick);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandUser : public ACommand
{
  private:
    std::string username;
    std::string realname;

  public:
    CommandUser(std::string);
    ~CommandUser();
    CommandUser(const CommandUser &commandUser);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandQuit : public ACommand
{
  private:
    std::string message;

  public:
    CommandQuit(std::string);
    ~CommandQuit();
    CommandQuit(const CommandQuit &commandQuit);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandJoin : public ACommand
{
  private:
    std::vector<std::string> channels;
    std::vector<std::string> keys;

  public:
    CommandJoin(std::vector<std::string>, std::vector<std::string>);
    ~CommandJoin();
    CommandJoin(const CommandJoin &commandJoin);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandCap : public ACommand
{
  private:
    std::string subcommand;
    std::string capability;

  public:
    CommandCap(std::string, std::string);
    ~CommandCap();
    CommandCap(const CommandCap &commandCap);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandPing : public ACommand
{
  private:
    std::string server;

  public:
    CommandPing(std::string);
    ~CommandPing();
    CommandPing(const CommandPing &commandPing);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandMode : public ACommand
{
  private:
    std::string                                      target;
    std::vector<std::pair<std::string, std::string>> modes;

  public:
    CommandMode(std::string, std::vector<std::pair<std::string, std::string>>);
    ~CommandMode();
    CommandMode(const CommandMode &commandMode);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandWho : public ACommand
{
  private:
    std::string mask;
    bool        o;

  public:
    CommandWho(std::string, bool);
    ~CommandWho();
    CommandWho(const CommandWho &commandWho);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandPrivmsg : public ACommand
{
  private:
    std::string target;
    std::string message;

  public:
    CommandPrivmsg(std::string, std::string);
    ~CommandPrivmsg();
    CommandPrivmsg(const CommandPrivmsg &commandPrivmsg);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandNotice : public ACommand
{
  private:
    std::string target;
    std::string message;

  public:
    CommandNotice(std::string, std::string);
    ~CommandNotice();
    CommandNotice(const CommandNotice &commandNotice);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandKick : public ACommand
{
  private:
    std::string channel;
    std::string user;
    std::string reason;

  public:
    CommandKick(std::string, std::string, std::string);
    ~CommandKick();
    CommandKick(const CommandKick &commandKick);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandPart : public ACommand
{
  private:
    std::vector<std::string> channels;
    std::string              message;

  public:
    CommandPart(std::vector<std::string>, std::string);
    ~CommandPart();
    CommandPart(const CommandPart &commandPart);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandTopic : public ACommand
{
  private:
    std::string channel;
    std::string message;

  public:
    CommandTopic(std::string, std::string);
    ~CommandTopic();
    CommandTopic(const CommandTopic &commandTopic);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandNames : public ACommand
{
  private:
    std::vector<std::string> channels;

  public:
    CommandNames(std::vector<std::string>);
    ~CommandNames();
    CommandNames(const CommandNames &commandNames);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandList : public ACommand
{
  private:
    std::set<std::string> channels;

  public:
    CommandList(std::set<std::string>);
    ~CommandList();
    CommandList(const CommandList &commandList);

    void execute(const Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

// class CommandDcc : public ACommand
// {
//   public:
//     CommandDcc(std::string);
//     ~CommandDcc();
//     CommandDcc(const CommandDcc &commandDcc);

//     void execute(const Client *, const Server &);
//     bool canExecute(const Client *, const Server &);
// };

#endif // COMMANDS_HPP
