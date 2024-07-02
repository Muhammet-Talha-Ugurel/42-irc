#ifndef USER_COMMAND_HPP

#define USER_COMMAND_HPP

#include "User.hpp"
#include "../cmd/ACommand.hpp"

class UserCommand
{
  public:
    User     &user;
    ACommand &command;
};

#endif // !USER_COMMAND_HPP