#ifndef COMMAND_MANAGER_HPP
#define COMMAND_MANAGER_HPP

#include "ACommand.hpp"
#include <string>
#include <vector>


class CommandManager
{
  private:
    CommandManager();
    CommandManager(CommandManager &commandManager);

  public:
    ~CommandManager();

    static CommandManager &getInstance();

		std::vector<ACommand *> parseCommand(std::string command);
};

#endif // !COMMAND_MANAGER_HPP
