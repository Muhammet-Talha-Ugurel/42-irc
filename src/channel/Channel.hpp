#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include "../client/ClientManager.hpp"
#include "../password/APassword.hpp"
#include "../user/User.hpp"

#include <set>
#include <string>

class Channel
{
  public:
    Channel(std::string name);
    Channel(std::string name, APassword password);
    Channel(const Channel &channel);
    ~Channel();

    void                         addUser(User *);
    void                         removeUser(User *);

    const std::set<const User *> getUsers() const;

    std::string                  getTopic();
    void                         setTopic(std::string);

    std::string                  getName();
    void                         setName(std::string);

    bool                         isPrivate();
    void                         setPrivate(bool);

    const APassword             &getPassword() const;
    void                         setPassword(APassword);

    void                         publishMessage(const std::string &, const ClientManager &);

  private:
    std::string            _name;
    std::string            _topic;
    APassword              _password;
    bool                   _isPrivate;

    std::set<const User *> _users;
    std::set<const User *> _mods;
};

#endif // !CHANNEL_HPP
