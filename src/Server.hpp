#ifndef SERVER_HPP

#define SERVER_HPP

#include "channel/ChannelManager.hpp"
#include "client/ClientManager.hpp"
#include "cmd/CommandManager.hpp"
#include "password/Password.hpp"
#include "password/PasswordManager.hpp"
#include "user/UserManager.hpp"

#include <string>

class Server
{
  public:
    Server(unsigned short port, std::string passwordString);
    ~Server();

    unsigned short   getPort() const { return _port; }
    const Password  &getPassword() const { return _password; }
    void             setPassword(const Password &password) { _password = password; }

    PasswordManager *getPasswordManager() const { return _password_manager; }
    ClientManager   *getClientManager() const { return _client_manager; }
    CommandManager  *getCommandManager() const { return _command_handler; }
    ChannelManager  *getChannelManager() const { return _channel_manager; }
    UserManager     *getUserManager() const { return _user_manager; }

    std::string respond(std::string code, const Client *client, std::string message = "") const;
    std::string respond(std::string code, const Client *client, std::string message = "");

    void        start();

  private:
    int              _socket_fd;
    unsigned short   _port;
    Password         _password;

    PasswordManager *_password_manager;
    CommandManager  *_command_handler;
    ClientManager   *_client_manager;
    ChannelManager  *_channel_manager;
    UserManager     *_user_manager;
};

#endif // !SERVER_HPP
