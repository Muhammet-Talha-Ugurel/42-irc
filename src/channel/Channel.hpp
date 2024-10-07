#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include "../user/User.hpp"
#include "../password/APassword.hpp"

#include <set>
#include <string>

class Channel
{
  public:
    Channel(std::string name);
    Channel(std::string name, std::string password);
    Channel(const Channel &channel);
    ~Channel();

    void             addUser(User *);
    void             removeUser(User *);
    std::set<User *> getUsers();

    void             publishMessage(std::string, User *);

    std::string      getTopic();
    void             setTopic(std::string);

    std::string      getName();
    void             setName(std::string);

    bool             isPrivate();
    void             setPrivate(bool);

    const APassword *getPassword();

  private:
    std::string      _name;
    std::string      _topic;
    APassword       *_password;
    bool             _isPrivate;

    std::set<User *> _users;
};

#endif // !CHANNEL_HPP