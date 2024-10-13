#ifndef COMMAND_MANAGER_HPP

#define COMMAND_MANAGER_HPP

#include "ACommand.hpp"

#include <string>
#pragma once

class CommandManager
{
  private:
    CommandManager();
    CommandManager(CommandManager &commandManager);

  public:
    ~CommandManager();

    static CommandManager &getInstance();

    ACommand              *parseCommand(std::string command);
};

#endif // !COMMAND_MANAGER_HPP
