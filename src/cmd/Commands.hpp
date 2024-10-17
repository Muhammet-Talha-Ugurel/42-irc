#ifndef COMMANDS_HPP

#include "../Server.hpp"
#include "ACommand.hpp"

#include <set>
#include <string>
#include <utility>
#include <vector>

using std::pair;
using std::set;
using std::string;
using std::vector;

enum ModeOperation
{
  O,
  B,
  I,
  T,
  N,
  K,
  L,
  S,
  P
};

class CommandPass : public ACommand
{
  private:
    string password;

  public:
    CommandPass(string);
    ~CommandPass();
    CommandPass(const CommandPass &);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandNick : public ACommand
{
  private:
    string nickname;

  public:
    CommandNick(string);
    ~CommandNick();
    CommandNick(const CommandNick &commandNick);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandUser : public ACommand
{
  private:
    string username;
    string realname;

  public:
    CommandUser(string, string);
    ~CommandUser();
    CommandUser(const CommandUser &commandUser);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandQuit : public ACommand
{
  private:
    string message;

  public:
    CommandQuit(string);
    ~CommandQuit();
    CommandQuit(const CommandQuit &commandQuit);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandJoin : public ACommand
{
  private:
    vector<string> channels;
    vector<string> keys;

  public:
    CommandJoin(vector<string>, vector<string>);
    ~CommandJoin();
    CommandJoin(const CommandJoin &commandJoin);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandCap : public ACommand
{
  public:
    CommandCap();
    ~CommandCap();
    CommandCap(const CommandCap &commandCap);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandPing : public ACommand
{
  private:
    string server;

  public:
    CommandPing(string);
    ~CommandPing();
    CommandPing(const CommandPing &commandPing);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandMode : public ACommand
{
  private:
    string                               target;
    bool                                 add;
    vector<pair<ModeOperation, string> > modes;

    void                                 execUserModes(Client *, const Server &);
    void                                 execChannelModes(const Server &);

  public:
    CommandMode(string, bool, vector<pair<ModeOperation, string> >);
    ~CommandMode();
    CommandMode(const CommandMode &commandMode);

    static ACommand *parseCommand(const string &);
    void             execute(Client *, const Server &);
    void             execute(const Client *, const Server &);
    bool             canExecute(Client *, const Server &);
    bool             canExecute(const Client *, const Server &);
};

class CommandWho : public ACommand
{
  private:
    string mask;
    bool   o;

  public:
    CommandWho(string, bool);
    ~CommandWho();
    CommandWho(const CommandWho &commandWho);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandPrivmsg : public ACommand
{
  private:
    string target;
    string message;

  public:
    CommandPrivmsg(string, string);
    ~CommandPrivmsg();
    CommandPrivmsg(const CommandPrivmsg &commandPrivmsg);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandNotice : public ACommand
{
  private:
    string target;
    string message;

  public:
    CommandNotice(string, string);
    ~CommandNotice();
    CommandNotice(const CommandNotice &commandNotice);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandKick : public ACommand
{
  private:
    string channel;
    string nickname;
    string reason;

  public:
    CommandKick(string c, string u, string r) : channel(c), nickname(u), reason(r)
    {
      _type = KICK;
    };
    ~CommandKick() {};
    CommandKick(const CommandKick &o) : channel(o.channel), nickname(o.nickname), reason(o.reason)
    {
      _type = o._type;
    };

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandPart : public ACommand
{
  private:
    vector<string> channels;
    string         message;

  public:
    CommandPart(vector<string>, string);
    ~CommandPart();
    CommandPart(const CommandPart &commandPart);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandTopic : public ACommand
{
  private:
    string channel;
    string topic;

  public:
    CommandTopic(string, string);
    ~CommandTopic();
    CommandTopic(const CommandTopic &commandTopic);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandNames : public ACommand
{
  private:
    vector<string> channels;

  public:
    CommandNames(vector<string>);
    ~CommandNames();
    CommandNames(const CommandNames &commandNames);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandList : public ACommand
{
  private:
    set<string> channels;

  public:
    CommandList(set<string>);
    ~CommandList();
    CommandList(const CommandList &commandList);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class Exception : public ACommand
{
  private:
    string code;
    string message;

  public:
    Exception(string m) : message(m) { _type = EXCEPTION; };
    ~Exception() {}
    Exception(const Exception &other) : message(other.message) { _type = other._type; };

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

class CommandInvite : public ACommand
{
  private:
		std::string invitedNick;
		std::string channelName;

  public:
    CommandInvite(std::string, std::string);
    ~CommandInvite();
    CommandInvite(const CommandInvite &commandInvite);

    void execute(Client *, const Server &);
    void execute(const Client *, const Server &);
    bool canExecute(Client *, const Server &);
    bool canExecute(const Client *, const Server &);
};

// class CommandDcc : public ACommand
// {
//   public:
//     CommandDcc(string);
//     ~CommandDcc();
//     CommandDcc(const CommandDcc &commandDcc);

//     void execute(Client *, const Server &);
//     void execute(const Client *, const Server &);
//     bool canExecute(Client *, const Server &);
//     bool canExecute(const Client *, const Server &);
// };

#endif // COMMANDS_HPP
