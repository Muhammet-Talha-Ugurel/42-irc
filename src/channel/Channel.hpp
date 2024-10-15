#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include "../client/ClientManager.hpp"
#include "../password/Password.hpp"
#include "../user/User.hpp"

#include <set>
#include <string>

class Channel
{
  public:
    Channel(std::string name);
    Channel(std::string name, Password password);
    Channel(const Channel &channel);
    ~Channel() {}

    std::string                  getTopic() const { return _topic; }
    void                         setTopic(std::string topic) { _topic = topic; }

    std::string                  getName() const { return _name; }
    void                         setName(std::string name) { _name = name; }

    bool                         isPrivate() const { return _isPrivate; }
    void                         setPrivate(bool t) { _isPrivate = t; }

    bool                         isSecret() const { return _isSecret; }
    void                         setSecret(bool t) { _isSecret = t; }

    const Password              &getPassword() const { return _password; }
    void                         setPassword(Password &password) { _password = password; }

    void                         addUser(const User *user) { _users.insert(user); }
    void                         removeUser(const User *user) { _users.erase(user); }
    const std::set<const User *> getUsers() const { return _users; }
    std::string                  getUserCountString() const;

    void                         addOperator(const User *user) { _oprs.insert(user); }
    const std::set<const User *> getOperators() const { return _oprs; }
    void                         removeOperator(const User *user) { _oprs.erase(user); }
    std::string                  getOperatorCountString() const;

    std::string                  getUserListString();

    bool hasUser(const User *user) const { return _users.find(user) != _users.end(); }
    bool hasOperator(const User *user) const { return _oprs.find(user) != _oprs.end(); }
    bool isUserBanned(const User *) const;

    void publishMessage(const std::string &, const Client &sender, const ClientManager &);

  private:
    std::string            _name;
    std::string            _topic;
    Password               _password;
    bool                   _isPrivate;
    bool                   _isSecret;

    std::set<const User *> _users;
    std::set<const User *> _oprs;
    std::set<const User *> _banned;
};

#endif // !CHANNEL_HPP
