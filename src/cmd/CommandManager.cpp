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
								if (pass != 0x00)
										commands.push_back(pass);
						}
						else if (cmd == "NICK") {
								iss >> arg;
								ACommand *nick = new CommandNick(arg);
								if (nick != 0x00)
										commands.push_back(nick);
						}
						else if (cmd == "USER") {
								iss >> arg;
								iss >> arg2;
								ACommand *user = new CommandUser(arg, arg2);
								if (user != 0x00)
										commands.push_back(user);
						}
						else if (cmd == "QUIT") {
								iss >> arg;
								// ACommand *quit = new CommandQuit(arg);
								// if (quit != 0x00)
										// commands.push_back(quit);
						}
						else if (cmd == "JOIN") {
								std::vector<std::string> channels;
								std::vector<std::string> keys;
								iss >> arg;
								if (arg[0] == '#')
										arg.erase(0, 1);
								channels.push_back(arg);
								ACommand *join = new CommandJoin(channels, keys);
								if (join != 0x00)
										commands.push_back(join);
						}
						else if (cmd == "CAP") {
								iss >> arg;
						}
						else if (cmd == "PING") {
								iss >> arg;
								ACommand *ping = new CommandPing(arg);
								if (ping != 0x00)
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
								iss >> arg2;
								if (arg[0] == ':')
										arg.erase(0, 1);
								ACommand *msg = new CommandPrivmsg(arg, arg2);
								if (msg != 0x00)
										commands.push_back(msg);
						}
						else if (cmd == "NOTICE") {
								iss >> arg;
						}
						else if (cmd == "KICK") {
								iss >> arg;
						}
						else if (cmd == "PART") {
								iss >> arg;
						}
						else if (cmd == "TOPIC") {
								iss >> arg;
						}
						else if (cmd == "NAMES") {
								iss >> arg;
						}
						else if (cmd == "LIST") {
								iss >> arg;
						}
						else if (cmd == "DCC") {
								iss >> arg;
						}
				}
		}
		return commands;
}
