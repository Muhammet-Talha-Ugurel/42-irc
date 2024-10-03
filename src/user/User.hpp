#ifndef USER_HPP
#define USER_HPP

#include "../password/APassword.hpp"

#include <string>

class User
{
  public:
    User();
    User(const User &);
    ~User();

    const std::string &getUsername() const;
    void               setUsername(const std::string &);

    const std::string &getRealName() const;
    void               setRealName(const std::string &);

    const APassword   &getPassword() const;
    void               setPassword(APassword);

    const std::string &getNickname() const;
    void               setNickname(const std::string &);

  private:
    std::string username;
    std::string nickname;
    std::string real_name;
    APassword   password;
};

#endif // !USER_HPP
