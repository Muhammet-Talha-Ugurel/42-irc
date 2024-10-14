#include "User.hpp"

User::User() {}

User::User(const User &other)
{
  _username  = other._username;
  _real_name = other._real_name;
  _password  = other._password;
}

User::~User() {}

const User &User::operator=(const User &other)
{
  _username      = other._username;
  _real_name     = other._real_name;
  _last_nickname = other._last_nickname;
  _password      = other._password;
  return *this;
}

bool User::operator==(const User &other) const { return _username == other._username; }

bool User::operator!=(const User &other) const { return _username != other._username; }

bool User::operator<(const User &other) const { return _username < other._username; }

bool User::operator>(const User &other) const { return _username > other._username; }
