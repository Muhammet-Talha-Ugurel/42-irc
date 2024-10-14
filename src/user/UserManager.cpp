
#include "UserManager.hpp"

#include <stdexcept>

UserManager::UserManager() {}

UserManager::~UserManager() {}

UserManager &UserManager::getInstance()
{
  static UserManager instance;
  return instance;
}

const User *UserManager::createUser(const User &toCreate)
{
  User toInsert = User(toCreate);
  this->_users.insert(toInsert);
  return &(*this->_users.find(toInsert));
}

const User *UserManager::updateUserByUsername(const std::string &username, const User &updatedUser)
{
  const User *find = this->findUserByUsername(username);
  if (find) {
      User *toUpdate = const_cast<User *>(find);
      toUpdate->setUsername(updatedUser.getUsername());
      toUpdate->setRealName(updatedUser.getRealName());
      toUpdate->setLastNickname(updatedUser.getLastNickname());
      toUpdate->setPassword(const_cast<Password &>(updatedUser.getPassword()));
      return toUpdate;
    }
  return 0x00;
}

void UserManager::deleteUserByUsername(const std::string &username)
{
  const User *find = this->findUserByUsername(username);
  if (find) {
      this->_users.erase(*find);
    }
  throw std::invalid_argument("User not found");
}

const User *UserManager::findUserByNickname(const std::string &nickname) const
{
  for (std::set<User>::iterator it = this->_users.begin(); it != this->_users.end(); ++it) {
      if (it->getLastNickname() == nickname) {
          return &(*it);
        }
    }
  return 0x00;
}

const User *UserManager::findUserByUsername(const std::string &username) const
{
  for (std::set<User>::iterator it = this->_users.begin(); it != this->_users.end(); ++it) {
      if (it->getUsername() == username) {
          return &(*it);
        }
    }
  return 0x00;
}
