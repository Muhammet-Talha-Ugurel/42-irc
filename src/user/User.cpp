#include "User.hpp"

User::User() {}

User::User(const User &other)
{
  username  = other.username;
  real_name = other.real_name;
  password  = other.password;
}

User::~User() {}

const std::string &User::getUsername() const { return username; }

void               User::setUsername(const std::string &username) { this->username = username; }

const std::string &User::getRealName() const { return real_name; }

void               User::setRealName(const std::string &real_name) { this->real_name = real_name; }

const Password    *User::getPassword() const { return password; }

void               User::setPassword(Password *password) { this->password = password; }

const std::string &User::getLastNickname() const { return last_nickname; }

void               User::setLastNickname(const std::string &last_nickname)
{
  this->last_nickname = last_nickname;
}

const User &User::operator=(const User &other)
{
  username      = other.username;
  real_name     = other.real_name;
  last_nickname = other.last_nickname;
  password      = other.password;
  return *this;
}

bool User::operator==(const User &other) const { return username == other.username; }

bool User::operator!=(const User &other) const { return username != other.username; }

bool User::operator<(const User &other) const { return username < other.username; }

bool User::operator>(const User &other) const { return username > other.username; }
