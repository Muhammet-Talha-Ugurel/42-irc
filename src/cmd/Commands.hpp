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
    CommandPass(std::string);
    ~CommandPass();
    CommandPass(const CommandPass &);

    void execute(const Client *);
    bool canExecute(const Client *);
};

// class CommandNick : public ACommand
// {
//   private:
//     std::string nickname;

//   public:
//     CommandNick(std::string);
//     ~CommandNick();
//     CommandNick(const CommandNick &commandNick);

//     void execute();
//     bool canExecute();
// };

// class CommandUser : public ACommand
// {
//   private:
//     std::string username;
//     std::string realname;

//   public:
//     CommandUser(std::string);
//     ~CommandUser();
//     CommandUser(const CommandUser &commandUser);

//     void execute();
//     bool canExecute();
// };

// class CommandQuit : public ACommand
// {
//   private:
//     std::string message;

//   public:
//     CommandQuit(std::string);
//     ~CommandQuit();
//     CommandQuit(const CommandQuit &commandQuit);

//     void execute();
//     bool canExecute();
// };

// class CommandJoin : public ACommand
// {
//   private:
//     std::vector<std::string> channels;
//     std::vector<std::string> keys;

//   public:
//     CommandJoin(std::string);
//     ~CommandJoin();
//     CommandJoin(const CommandJoin &commandJoin);

//     void execute();
//     bool canExecute();
// };

// class CommandCap : public ACommand
// {
//   private:
//     std::string subcommand;
//     std::string capability;

//   public:
//     CommandCap(std::string);
//     ~CommandCap();
//     CommandCap(const CommandCap &commandCap);

//     void execute();
//     bool canExecute();
// };

// class CommandPing : public ACommand
// {
//   private:
//     std::string server;

//   public:
//     CommandPing(std::string);
//     ~CommandPing();
//     CommandPing(const CommandPing &commandPing);

//     void execute();
//     bool canExecute();
// };

// class CommandMode : public ACommand
// {
//   private:
//     std::string                                      target;
//     std::vector<std::pair<std::string, std::string>> modes;

//   public:
//     CommandMode(std::string);
//     ~CommandMode();
//     CommandMode(const CommandMode &commandMode);

//     void execute();
//     bool canExecute();
// };

// class CommandWho : public ACommand
// {
//   private:
//     std::string mask;
//     bool        o;

//   public:
//     CommandWho(std::string);
//     ~CommandWho();
//     CommandWho(const CommandWho &commandWho);

//     void execute();
//     bool canExecute();
// };

// class CommandPrivmsg : public ACommand
// {
//   private:
//     std::string target;
//     std::string message;

//   public:
//     CommandPrivmsg(std::string);
//     ~CommandPrivmsg();
//     CommandPrivmsg(const CommandPrivmsg &commandPrivmsg);

//     void execute();
//     bool canExecute();
// };

// class CommandNotice : public ACommand
// {
//   private:
//     std::string target;
//     std::string message;

//   public:
//     CommandNotice(std::string);
//     ~CommandNotice();
//     CommandNotice(const CommandNotice &commandNotice);

//     void execute();
//     bool canExecute();
// };

// class CommandKick : public ACommand
// {
//   private:
//     std::string channel;
//     std::string user;
//     std::string reason;

//   public:
//     CommandKick(std::string);
//     ~CommandKick();
//     CommandKick(const CommandKick &commandKick);

//     void execute();
//     bool canExecute();
// };

// class CommandPart : public ACommand
// {
//   private:
//     std::vector<std::string> channels;
//     std::string              message;

//   public:
//     CommandPart(std::string);
//     ~CommandPart();
//     CommandPart(const CommandPart &commandPart);

//     void execute();
//     bool canExecute();
// };

// class CommandTopic : public ACommand
// {
//   private:
//     std::string channel;
//     std::string message;

//   public:
//     CommandTopic(std::string);
//     ~CommandTopic();
//     CommandTopic(const CommandTopic &commandTopic);

//     void execute();
//     bool canExecute();
// };

// class CommandNames : public ACommand
// {
//   private:
//     std::vector<std::string> channels;

//   public:
//     CommandNames(std::string);
//     ~CommandNames();
//     CommandNames(const CommandNames &commandNames);

//     void execute();
//     bool canExecute();
// };

class CommandList : public ACommand
{
  private:
    std::vector<std::string> channels;

  public:
    CommandList(std::string);
    ~CommandList();
    CommandList(const CommandList &commandList);

    void execute();
    bool canExecute();
};

// class CommandDcc : public ACommand
// {
//   public:
//     CommandDcc(std::string);
//     ~CommandDcc();
//     CommandDcc(const CommandDcc &commandDcc);

//     void execute();
//     bool canExecute();
// };

#endif // COMMANDS_HPP
