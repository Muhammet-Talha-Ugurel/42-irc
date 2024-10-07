#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include "User.hpp"

#include <set>

class UserManager
{
  private:
    std::set<User> _users;

  public:
    UserManager();
    UserManager(const UserManager &);
    ~UserManager();

    static const UserManager INSTANCE;

    const User *createUser(const User &);
    const User *updateUser(const User &);

    void        deleteUserByUsername(std::string username);

    std::set<const User *> findAllUserByNickname(const std::string &) const;
    std::set<const User *> findAllUserByUsername(const std::string &) const;
};

static UserManager INSTANCE;

#endif // !USER_MANAGER_HPP