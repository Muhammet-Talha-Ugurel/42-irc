#include "CommandManager.hpp"

#include "ACommand.hpp"
#include "CommandUtils.hpp"
#include "Commands.hpp"

#include <iostream>
#include <sstream>
#include <string>

void                  announce(string message) { std::cout << message << std::endl; }

static vector<string> splitByDelim(string str, char c)
{
  vector<string>    result;
  std::stringstream ss(str);
  string            one;

  while (std::getline(ss, one, c))
    result.push_back(one);

  return result;
}

CommandManager::CommandManager() {}

CommandManager::CommandManager(CommandManager &commandHandler) { (void)commandHandler; }

CommandManager::~CommandManager() {}

CommandManager &CommandManager::getInstance()
{
  static CommandManager instance;
  return instance;
}

vector<ACommand *> CommandManager::parseCommand(string command)
{
  vector<ACommand *> commands;
  std::istringstream stream(command);
  string             line;
  while (std::getline(stream, line))
  {
    std::istringstream iss(line);
    string             cmd, arg, arg2;
    while (iss >> cmd)
    {
      if (cmd == "PASS")
      {
        iss >> arg;
        if (arg[0] == ':')
          arg.erase(0, 1);
        ACommand *pass = new CommandPass(arg);
        if (pass != NULL)
          commands.push_back(pass);
      }
      else if (cmd == "NICK")
      {
        iss >> arg;
        ACommand *nick = new CommandNick(arg);
        if (nick != NULL)
          commands.push_back(nick);
      }
      else if (cmd == "USER")
      {
        iss >> arg;
        iss >> arg2;
        iss >> arg2;
        std::getline(iss, arg2);
        arg2.erase(0, 4);
        std::cout << arg2 << std::endl;
        ACommand *user = new CommandUser(arg, arg2);
        if (user != NULL)
          commands.push_back(user);
      }
      else if (cmd == "QUIT")
      {
        iss >> arg;
        ACommand *quit = new CommandQuit(arg);
        if (quit != NULL)
          commands.push_back(quit);
      }
      else if (cmd == "JOIN")
      {
        iss >> arg;
        iss >> arg2;
        vector<string> channels = splitByDelim(arg, ',');
        vector<string> keys     = splitByDelim(arg2, ',');
        ACommand      *join     = new CommandJoin(channels, keys);
        if (join != NULL)
        {
          commands.push_back(join);
          commands.push_back(new CommandNames(channels));
        }
      }
      else if (cmd == "CAP")
      {
        ACommand *cap = new CommandCap();
        if (cap != NULL)
          commands.push_back(cap);
      }
      else if (cmd == "PING")
      {
        iss >> arg;
        ACommand *ping = new CommandPing(arg);
        if (ping != NULL)
          commands.push_back(ping);
      }
      else if (cmd == "MODE")
      {
        try
        {
          ACommand *mode = CommandMode::parseCommand(command);
          if (mode != NULL)
            commands.push_back(mode);
        }
        catch (std::exception &e)
        {
          commands.push_back(new Exception(e.what()));
        }
      }
      else if (cmd == "WHO")
      {
        bool o = false;
        int  i = countWords(iss);
        iss.clear();
        iss.seekg(0);
        if (i == 0 || i > 2)
        {
          commands.push_back(NULL);
          continue;
        }
        iss >> arg;
        iss >> arg;
        if (arg == "o")
        {
          commands.push_back(NULL);
          continue;
        }
        if (i == 2)
        {
          iss >> arg2;
          if (arg2 == "o")
            o = true;
        }
        std::cout << arg << std::endl;
        ACommand *who = new CommandWho(arg, o);
        if (who != NULL)
          commands.push_back(who);
      }
      else if (cmd == "PRIVMSG")
      {
        iss >> arg;
        if (arg[0] == '#')
          arg.erase(0, 1);
        arg2 = iss.str();
        if (arg2[0] == ':')
          arg2.erase(0, 1);
        ACommand *msg = new CommandPrivmsg(arg, arg2);
        if (msg != NULL)
          commands.push_back(msg);
      }
      else if (cmd == "NOTICE")
      {
        iss >> arg;
        if (arg[0] == '#')
          arg.erase(0, 1);
        arg2 = iss.str();
        if (arg2[0] == ':')
          arg2.erase(0, 1);
        ACommand *notice = new CommandNotice(arg, arg2);
        if (notice != NULL)
          commands.push_back(notice);
      }
      else if (cmd == "KICK")
      {
        iss >> arg;
        iss >> arg2;
        iss >> cmd;
        if (!cmd.empty() && cmd[0] == ':')
          cmd = cmd.substr(1);
        commands.push_back(new CommandKick(arg, arg2, cmd));
      }
      else if (cmd == "PART")
      {
        iss >> arg;
        vector<string> channels = splitByDelim(arg, ',');
        iss >> arg;
        vector<string> keys = splitByDelim(arg, ',');
        channels.push_back(arg);
        arg2 = iss.str();
        if (arg2[0] == ':')
          arg2.erase(0, 1);
        ACommand *part = new CommandPart(channels, arg2);
        if (part != NULL)
          commands.push_back(part);
      }
      else if (cmd == "TOPIC")
      {
        iss >> arg;
        iss >> arg2;
      }
      else if (cmd == "NAMES")
      {
        iss >> arg;
        vector<string> channels = splitByDelim(arg, ',');
        ACommand      *names    = new CommandNames(channels);
        if (names)
          commands.push_back(names);
      }
      else if (cmd == "LIST")
      {
        std::set<string> channels;
        string           keys;
        iss >> arg;
        if (arg[0] == '#')
          arg.erase(0, 1);
        channels.insert(arg);
        ACommand *list = new CommandList(channels);
        if (list != NULL)
          commands.push_back(list);
      }
    }
  }
  return commands;
}
