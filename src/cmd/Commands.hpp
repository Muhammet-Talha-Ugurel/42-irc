#include <utility>
#include <vector>
#ifndef COMMANDS_HPP
#pragma once

#include "ACommand.hpp"

class CommandPass : public ACommand
{
  private:
    std::string password;

  public:
    CommandPass(Client *client, std::string pass);
    ~CommandPass();
    CommandPass(const CommandPass &commandPass);

    void execute();
    bool canExecute();
};

//class CommandNick : public ACommand
//{
//  private:
//    std::string nickname;
//
//  public:
//    CommandNick(Client *client) : ACommand(NICK, client) {};
//    ~CommandNick();
//    CommandNick(const CommandNick &commandNick);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandUser : public ACommand
//{
//  private:
//    std::string username;
//    std::string realname;
//
//  public:
//    CommandUser(Client *client) : ACommand(USER, client) {};
//    ~CommandUser();
//    CommandUser(const CommandUser &commandUser);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandQuit : public ACommand
//{
//  private:
//    std::string message;
//
//  public:
//    CommandQuit(Client *client) : ACommand(QUIT, client) {};
//    ~CommandQuit();
//    CommandQuit(const CommandQuit &commandQuit);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandJoin : public ACommand
//{
//  private:
//    std::vector<std::string> channels;
//    std::vector<std::string> keys;
//
//  public:
//    CommandJoin(Client *client) : ACommand(JOIN, client) {};
//    ~CommandJoin();
//    CommandJoin(const CommandJoin &commandJoin);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandCap : public ACommand
//{
//  private:
//    std::string subcommand;
//    std::string capability;
//
//  public:
//    CommandCap(Client *client) : ACommand(CAP, client) {};
//    ~CommandCap();
//    CommandCap(const CommandCap &commandCap);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandPing : public ACommand
//{
//  private:
//    std::string server;
//
//  public:
//    CommandPing(Client *client) : ACommand(PING, client) {};
//    ~CommandPing();
//    CommandPing(const CommandPing &commandPing);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandMode : public ACommand
//{
//  private:
//    std::string                                      target;
//    std::vector<std::pair<std::string, std::string>> modes;
//
//  public:
//    CommandMode(Client *client) : ACommand(MODE, client) {};
//    ~CommandMode();
//    CommandMode(const CommandMode &commandMode);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandWho : public ACommand
//{
//  private:
//    std::string mask;
//    bool        o;
//
//  public:
//    CommandWho(Client *client) : ACommand(WHO, client) {};
//    ~CommandWho();
//    CommandWho(const CommandWho &commandWho);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandPrivmsg : public ACommand
//{
//  private:
//    std::string target;
//    std::string message;
//
//  public:
//    CommandPrivmsg(Client *client) : ACommand(PRIVMSG, client) {};
//    ~CommandPrivmsg();
//    CommandPrivmsg(const CommandPrivmsg &commandPrivmsg);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandNotice : public ACommand
//{
//  private:
//    std::string target;
//    std::string message;
//
//  public:
//    CommandNotice(Client *client) : ACommand(NOTICE, client) {};
//    ~CommandNotice();
//    CommandNotice(const CommandNotice &commandNotice);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandKick : public ACommand
//{
//  private:
//    std::string channel;
//    std::string user;
//    std::string reason;
//
//  public:
//    CommandKick(Client *client) : ACommand(KICK, client) {};
//    ~CommandKick();
//    CommandKick(const CommandKick &commandKick);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandPart : public ACommand
//{
//  private:
//    std::vector<std::string> channels;
//    std::string              message;
//
//  public:
//    CommandPart(Client *client) : ACommand(PART, client) {};
//    ~CommandPart();
//    CommandPart(const CommandPart &commandPart);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandTopic : public ACommand
//{
//  private:
//    std::string channel;
//    std::string message;
//
//  public:
//    CommandTopic(Client *client) : ACommand(TOPIC, client) {};
//    ~CommandTopic();
//    CommandTopic(const CommandTopic &commandTopic);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandNames : public ACommand
//{
//  private:
//    std::vector<std::string> channels;
//
//  public:
//    CommandNames(Client *client) : ACommand(NAMES, client) {};
//    ~CommandNames();
//    CommandNames(const CommandNames &commandNames);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandList : public ACommand
//{
//  private:
//    std::vector<std::string> channels;
//
//  public:
//    CommandList(Client *client) : ACommand(LIST, client) {};
//    ~CommandList();
//    CommandList(const CommandList &commandList);
//
//    void execute();
//    bool canExecute();
//};
//
//class CommandDcc : public ACommand
//{
//  public:
//    CommandDcc(Client *client) : ACommand(DCC, client) {};
//    ~CommandDcc();
//    CommandDcc(const CommandDcc &commandDcc);
//
//    void execute();
//    bool canExecute();
//};

#endif // !COMMANDS_HPP
