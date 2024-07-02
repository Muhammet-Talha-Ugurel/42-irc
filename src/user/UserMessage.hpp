#ifndef USER_MESSAGE_HPP

#define USER_MESSAGE_HPP

#include "User.hpp"

#include <string>

class UserMessage
{
  public:
    UserMessage();
    ~UserMessage();

  private:
    User       &_user;
    std::string msg;
};

#endif // !USER_MESSAGE_HPP
