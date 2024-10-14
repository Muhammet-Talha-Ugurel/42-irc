#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include "User.hpp"

#include <set>

class UserManager
{
  private:
    std::set<User> _users;

    UserManager();

  public:
    UserManager(const UserManager &);
    UserManager &operator=(const UserManager &);
    ~UserManager();

    static UserManager &getInstance();

    const User         *createUser(const User &);
    const User         *updateUserByUsername(const std::string &, const User &);

    int                 deleteUser(const User &);
    void                deleteUserByUsername(const std::string &);

    const User         *findUserByNickname(const std::string &) const;
    const User         *findUserByUsername(const std::string &) const;
};

#endif // USER_MANAGER_HPP