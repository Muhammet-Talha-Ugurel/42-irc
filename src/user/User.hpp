#ifndef USER_HPP
#define USER_HPP

#include "../password/Password.hpp"

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

    const std::string &getLastNickname() const;
    void               setLastNickname(const std::string &);

    const Password    *getPassword() const;
    void               setPassword(Password *);

    bool               isVisible() const;
    void               setVisible(bool);

    const User        &operator=(const User &);
    bool               operator==(const User &) const;
    bool               operator!=(const User &) const;
    bool               operator<(const User &) const;
    bool               operator>(const User &) const;

  private:
    std::string username;
    std::string real_name;
    std::string last_nickname;
    Password   *password;
    bool        is_visible;
};

#endif // !USER_HPP
