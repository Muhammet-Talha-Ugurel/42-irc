#ifndef COMMAND_HANDLER_HPP

#define COMMAND_HANDLER_HPP

#include "ACommand.hpp"

#include <string>
#pragma once

class CommandHandler
{
  public:
    CommandHandler();
    ~CommandHandler();
    CommandHandler(CommandHandler &commandHandler);

    ACommand *parseCommand(std::string command);
};

#endif // !COMMAND_HANDLER_HPP