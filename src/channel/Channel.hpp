#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include "../client/ClientManager.hpp"
#include "../password/Password.hpp"
#include "../user/User.hpp"
#include "Ban.hpp"

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

    bool                         isInviteOnly() const { return _isInviteOnly; }
    void                         setInviteOnly(bool t) { _isInviteOnly = t; }

    bool                         isModerated() const { return _isModerated; }
    void                         setModerated(bool t) { _isModerated = t; }

    bool                         isTopicProtected() const { return _isTopicProtected; }
    void                         setTopicProtected(bool t) { _isTopicProtected = t; }

    bool                         isNoExternalMessages() const { return _isNoExternalMessages; }
    void                         setNoExternalMessages(bool t) { _isNoExternalMessages = t; }

    int                          getUserLimit() const { return _userLimit; }
    void                         setUserLimit(int limit) { _userLimit = limit; }

    const Password              &getPassword() const { return _password; }
    void                         setPassword(const Password &password) { _password = Password(password); }

    bool                         shouldDestroy() const { return _users.empty(); }

    std::set<Ban>                getBanMasks() { return _banned; }
    void                         addBanMask(std::string banner, std::string mask);
    void                         removeBanMask(std::string mask);
    std::set<User *>             findUsersByMask(const std::string &mask) const;
    Ban                          findBanMask(const std::string &mask) const;
    bool                         evalMask(const std::string &mask, const User *user) const;

    const std::set<const User *> getUsers() const { return _users; }
    void                         addUser(const User *user);
    void                         removeUser(const User *user);
    std::string                  getUserCountString() const;
    std::string                  getUserListString();

    const std::set<const User *> getOperators() const { return _oprs; }
    void                         addOperator(const User *user) { _oprs.insert(user); }
    void                         removeOperator(const User *user) { _oprs.erase(user); }
    std::string                  getOperatorCountString() const;

    void                         inviteUser(const User *user) { _invited.insert(user); }

    bool                         hasUser(const User *user) const { return _users.find(user) != _users.end(); }
    bool                         hasOperator(const User *user) const { return _oprs.find(user) != _oprs.end(); }
    bool                         hasInvite(const User *user) const { return _invited.find(user) != _invited.end(); }
    bool                         isBanned(const User *user) const;
    bool                         isFull() const { return _userLimit && _users.size() >= _userLimit; }

    void                         publishMessage(const std::string &, Client *sender, const ClientManager &);

  private:
    std::string            _name;
    std::string            _topic;
    Password               _password;
    bool                   _isPrivate;
    bool                   _isSecret;
    bool                   _isInviteOnly;
    bool                   _isModerated;
    bool                   _isTopicProtected;
    bool                   _isNoExternalMessages;
    unsigned long          _userLimit;

    std::set<const User *> _users;
    std::set<const User *> _oprs;
    std::set<const User *> _invited;
    std::set<Ban>          _banned;
};

#endif // !CHANNEL_HPP
