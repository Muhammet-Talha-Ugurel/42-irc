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

    std::string                  getTopic() const { return this->_topic; }
    void                         setTopic(std::string topic) { this->_topic = topic; }

    std::string                  getName() const { return this->_name; }
    void                         setName(std::string name) { this->_name = name; }

    bool                         isPrivate() const { return this->_isPrivate; }
    void                         setPrivate(bool) { this->_isPrivate = true; }

    const APassword             &getPassword() const { return this->_password; }
    void                         setPassword(APassword &password) { this->_password = password; }

    void                         addUser(User *);
    void                         removeUser(User *);

    const std::set<const User *> getUsers() const { return this->_users; }

    void                         publishMessage(const std::string &, const ClientManager &);

    void                         addMod(const User *);
    bool                         isUserBanned(const User *) const;

  private:
    std::string            _name;
    std::string            _topic;
    APassword              _password;
    bool                   _isPrivate;

    std::set<const User *> _users;
    std::set<const User *> _mods;
    std::set<const User *> _banned;
};

#endif // !CHANNEL_HPP
