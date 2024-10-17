#include "CommandManager.hpp"

#include "ACommand.hpp"
#include "CommandUtils.hpp"
#include "Commands.hpp"
#include <cstdio>
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
		size_t end = line.find_last_not_of("\r\n");
		if (end != std::string::npos) {
				line.erase(end + 1);
		} else {
				line.clear();
		}
		while (std::getline(stream, line))
		{
				std::istringstream iss(line);
				string             cmd, arg, arg2;
				while (iss >> cmd)
				{
						if (cmd == "PASS")
						{
								int  i = countWords(iss);
								iss >> arg;
								if (arg.empty())
								{
										commands.push_back(new Exception("No password specified"));
										continue;
								}
								if (i > 1)
								{
										commands.push_back(new Exception("PASS name only accepts one argument"));
										continue;
								}
								if (arg.length() > 31)
								{
										commands.push_back(new Exception("Password too long"));
										continue;
								}
								iss >> arg;
								if (arg[0] == ':')
										arg.erase(0, 1);
								ACommand *pass = new CommandPass(arg);
								if (pass != NULL)
										commands.push_back(pass);
						}
						else if (cmd == "NICK" || cmd == "nick")
						{
								int  i = countWords(iss);
								iss >> arg;
								iss >> arg;
								if (arg.empty())
								{
										commands.push_back(new Exception("No nickname specified"));
										continue;
								}
								if (arg.length() > 9)
								{
										commands.push_back(new Exception("Nickname too long"));
										continue;
								}
								if (i > 1)
								{
										commands.push_back(new Exception("Nick name only accepts one argument"));
										continue;
								}
								if (arg[0] == ':')
										arg.erase(0, 1);
								if (containsInvalidChars(arg)) {
										commands.push_back(new Exception("Invalid nickname"));
										continue;
								}
								ACommand *nick = new CommandNick(arg);
								if (nick != NULL)
										commands.push_back(nick);
						}
						else if (cmd == "USER" || cmd == "user")
						{
								int  i = countWords(iss);
								iss >> arg;
								if (i >= 4)
								{
										iss >> arg;
										if (containsInvalidChars(arg)) {
												commands.push_back(new Exception("Invalid username"));
												continue;
										}
										if (arg.length() > 16)
										{
												commands.push_back(new Exception("Username too long"));
												continue;
										}
										iss >> arg2;
										iss >> arg2;
										std::getline(iss, arg2);
										arg2.erase(0, 4);
										std::cout << arg2 << std::endl;
										if (arg2.length() > 255)
										{
												commands.push_back(new Exception("realname too long"));
												continue;
										}
										ACommand *user = new CommandUser(arg, arg2);
										if (user != NULL)
												commands.push_back(user);
								}
						}
						else if (cmd == "QUIT")
						{
								if (iss >> std::ws && iss.peek() == ':')
								{
										std::getline(iss, arg);
										arg.erase(0, 1);
								}
								ACommand *quit = new CommandQuit(arg);
								if (quit != NULL)
										commands.push_back(quit);
						}
						else if (cmd == "JOIN")
						{
								vector<string> channels;
								vector<string> keys;
								std::string channelsPart, passwordsPart;
								iss >> std::ws;
								std::getline(iss, channelsPart, ' ');
								std::getline(iss, passwordsPart, ' ');
								std::istringstream channelStream(channelsPart);
								std::string channel;
								while (std::getline(channelStream, channel, ',')) {
										channels.push_back(channel);
								}
								std::string password;
								std::istringstream passwordStream(passwordsPart);
								while (std::getline(passwordStream, password, ',')) {
										keys.push_back(password);
								}
								ACommand *join = new CommandJoin(channels, keys);
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
						else if (cmd == "MODE" || cmd == "mode")
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
										commands.push_back(new Exception(":421 :Unknown command"));
										continue;
								}
								iss >> arg;
								iss >> arg;
								if (arg == "o")
								{
										commands.push_back(new Exception(":421 :Unknown command"));
										continue;
								}
								if (i == 2)
								{
										iss >> arg2;
										if (arg2 == "o")
												o = true;
								}
								ACommand *who = new CommandWho(arg, o);
								if (who != NULL)
										commands.push_back(who);
						}
						else if (cmd == "PRIVMSG")
						{
								iss >> arg;
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
								arg2 = iss.str();
								if (arg2[0] == ':')
										arg2.erase(0, 1);
								ACommand *notice = new CommandNotice(arg, arg2);
								if (notice != NULL)
										commands.push_back(notice);
						}
						else if (cmd == "KICK" || cmd == "kick")
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
						else if (cmd == "INVITE")
						{
								iss >> arg;
								iss >> arg2;
								ACommand *invite = new CommandInvite(arg, arg2);
								if (invite != NULL)
										commands.push_back(invite);
						}
				}
		}
		return commands;
}
