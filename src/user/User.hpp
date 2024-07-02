#ifndef USER_HPP

#define USER_HPP

#include <string>

class User
{
  public:
	User();
	User(User &);
	~User();

    void        join_channel(std::string);
    void        quit_channel(std::string);

    std::string get_username();
    void        set_username(std::string);

    std::string get_real_name();
    void        set_real_name(std::string);

    std::string get_password_hash();
    void        set_password_hash(std::string);

  private:
    std::string username;
    std::string real_name;
    std::string password_hash;
};

#endif // !USER_HPP
