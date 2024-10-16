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

    const std::string &getUsername() const { return _username; };
    const std::string &getRealName() const { return _real_name; };
    const std::string &getLastNickname() const { return _last_nickname; };
    const Password    &getPassword() const { return _password; };
    bool               isVisible() const;

    void setLastNickname(const std::string &last_nickname) { _last_nickname = last_nickname; };
    void setUsername(const std::string &username) { _username = username; };
    void setRealName(const std::string &real_name) { _real_name = real_name; };
    void setPassword(Password &password) { _password = password; };
    void setVisible(bool) { _is_visible = true; };

    const User &operator=(const User &);
    bool        operator==(const User &) const;
    bool        operator!=(const User &) const;
    bool        operator<(const User &) const;
    bool        operator>(const User &) const;

  private:
    std::string _username;
    std::string _real_name;
    std::string _last_nickname;
    Password    _password;
    bool        _is_visible;
};

#endif // !USER_HPP
