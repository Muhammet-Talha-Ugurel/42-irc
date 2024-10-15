#include "CommandManager.hpp"
#include "Commands.hpp"

#include <iostream>
#include <sstream>
#include <string>

void announce(std::string message) { std::cout << message << std::endl; }

CommandManager::CommandManager() {}

CommandManager::CommandManager(CommandManager &commandHandler) { (void)commandHandler; }

CommandManager::~CommandManager() {}

CommandManager &CommandManager::getInstance()
{
		static CommandManager instance;
		return instance;
}

std::vector<ACommand *> CommandManager::parseCommand(std::string command)
{
		std::vector<ACommand *> commands;
		std::istringstream stream(command);
		std::string        line;
		while (std::getline(stream, line)) {
				std::istringstream iss(line);
				std::string        cmd, arg, arg2;
				while (iss >> cmd) {
						if (cmd == "PASS") {
								iss >> arg;
								if (arg[0] == ':')
										arg.erase(0, 1);
								ACommand *pass = new CommandPass(arg);
								if (pass != NULL)
										commands.push_back(pass);
						}
						else if (cmd == "NICK") {
								iss >> arg;
								ACommand *nick = new CommandNick(arg);
								if (nick != NULL)
										commands.push_back(nick);
						}
						else if (cmd == "USER") {
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
						else if (cmd == "QUIT") {
								iss >> arg;
								ACommand *quit = new CommandQuit(arg);
								if (quit != NULL)
										commands.push_back(quit);
						}
						else if (cmd == "JOIN") {
								std::vector<std::string> channels;
								std::vector<std::string> keys;
								iss >> arg;
								if (arg[0] == '#')
										arg.erase(0, 1);
								channels.push_back(arg);
								ACommand *join = new CommandJoin(channels, keys);
								if (join != NULL)
										commands.push_back(join);
						}
						else if (cmd == "CAP") {
								ACommand *cap = new CommandCap();
								if (cap != NULL)
										commands.push_back(cap);
						}
						else if (cmd == "PING") {
								iss >> arg;
								ACommand *ping = new CommandPing(arg);
								if (ping != NULL)
										commands.push_back(ping);
						}
						else if (cmd == "MODE") {
								iss >> arg;
						}
						else if (cmd == "WHO") {
								iss >> arg;
						}
						else if (cmd == "PRIVMSG") {
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
						else if (cmd == "NOTICE") {
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
						else if (cmd == "KICK") {
								iss >> arg;
						}
						else if (cmd == "PART") {
								std::vector<std::string> channels;
								std::string keys;
								iss >> arg;
								if (arg[0] == '#')
										arg.erase(0, 1);
								channels.push_back(arg);
								arg2 = iss.str();
								if (arg2[0] == ':')
										arg2.erase(0, 1);
								ACommand *part = new CommandPart(channels, arg2);
								if (part != NULL)
										commands.push_back(part);
						}
						else if (cmd == "TOPIC") {
								iss >> arg;
						}
						else if (cmd == "NAMES") {
								iss >> arg;
						}
						else if (cmd == "LIST") {
								std::set<std::string> channels;
								std::string keys;
								iss >> arg;
								if (arg[0] == '#')
										arg.erase(0, 1);
								channels.insert(arg);
								ACommand *list = new CommandList(channels);
								if (list != NULL)
										commands.push_back(list);
						}
						else if (cmd == "DCC") {
								iss >> arg;
						}
				}
		}
		return commands;
}
