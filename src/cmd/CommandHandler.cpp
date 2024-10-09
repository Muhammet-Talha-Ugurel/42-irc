#include "CommandHandler.hpp"

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
  (void)command;
  return 0x00;
}