#ifndef COMMAND_HANDLER_HPP

#define COMMAND_HANDLER_HPP

#include "ACommand.hpp"

#include <string>
#pragma once

class CommandHandler
{
  private:
    CommandHandler();
    CommandHandler(CommandHandler &commandHandler);

  public:
    ~CommandHandler();

    static CommandHandler &getInstance();

    ACommand              *parseCommand(std::string command);
};

#endif // !COMMAND_HANDLER_HPP
