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
								announce("PASS MESSAGE RECEIVED");
								iss >> arg;
								if (arg[0] == ':')
										arg.erase(0, 1);
								ACommand *pass = new CommandPass(arg);
								if (pass != 0x00)
										commands.push_back(pass);
						}
						else if (cmd == "NICK") {
								announce("NICK MESSAGE RECEIVED");
								iss >> arg;
								ACommand *nick = new CommandNick(arg);
								if (nick != 0x00)
										commands.push_back(nick);
						}
						else if (cmd == "USER") {
								announce("USER MESSAGE RECEIVED");
								std::cout << line << std::endl;
								iss >> arg;
								ACommand *nick = new CommandUser(arg, arg2);
								if (nick != 0x00)
										commands.push_back(nick);
						}
						else if (cmd == "QUIT") {
								announce("QUIT MESSAGE RECEIVED");
								iss >> arg;
								ACommand *quit = new CommandQuit(arg);
								if (quit != 0x00)
										commands.push_back(quit);
						}
						else if (cmd == "JOIN") {
								announce("JOIN MESSAGE RECEIVED");
								iss >> arg;
								ACommand *join = new CommandJoin();
								if (join != 0x00)
										commands.push_back(join);
						}
						else if (cmd == "CAP") {
								announce("CAP MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "PING") {
								announce("PING MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "MODE") {
								announce("MODE MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "WHO") {
								announce("WHO MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "PRIVMSG") {
								announce("PRIVMSG MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "NOTICE") {
								announce("NOTICE MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "KICK") {
								announce("KICK MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "PART") {
								announce("PART MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "TOPIC") {
								announce("TOPIC MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "NAMES") {
								announce("NAMES MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "LIST") {
								announce("LIST MESSAGE RECEIVED");
								iss >> arg;
						}
						else if (cmd == "DCC") {
								announce("DCC MESSAGE RECEIVED");
								iss >> arg;
						}
				}
		}
		return commands;
}
