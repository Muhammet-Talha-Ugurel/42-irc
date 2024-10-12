#include "CommandHandler.hpp"

#include <sstream>
#include <iostream>
#include <string>
#include "Commands.hpp"

CommandHandler::CommandHandler() {}

CommandHandler::CommandHandler(CommandHandler &commandHandler) { (void)commandHandler; }

CommandHandler::~CommandHandler() {}

CommandHandler &CommandHandler::getInstance()
{
  static CommandHandler instance;
  return instance;
}

ACommand *CommandHandler::parseCommand(std::string command)
{
    std::istringstream stream(command);
    std::string line;

    while(std::getline(stream, line))
		{
				std::cout << line << std::endl;
				std::istringstream iss(line);
				std::string cmd, arg;
				while (iss >> cmd)
				{
						if (cmd == "PASS") {
								iss >> arg;
								if (arg[0] == ':')
                    arg.erase(0, 1);
								ACommand *pass = new CommandPass(new Client(0,0,0,""), arg);
								return pass; 
						}
						else if (cmd == "NICK") {
								iss >> arg;
						}
						else if (cmd == "USER") {
								iss >> arg;
						}
						else if (cmd == "QUIT") {
								iss >> arg;
						}
						else if (cmd == "JOIN") {
								iss >> arg;
						}
						else if (cmd == "CAP") {
								iss >> arg;
						}
						else if (cmd == "PING") {
								iss >> arg;
						}
						else if (cmd == "MODE") {
								iss >> arg;
						}
						else if (cmd == "WHO") {
								iss >> arg;
						}
						else if (cmd == "PRIVMSG") {
								iss >> arg;
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
		return 0x00;
}
