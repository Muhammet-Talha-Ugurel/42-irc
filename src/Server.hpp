#ifndef SERVER_HPP

#define SERVER_HPP

#include "client/ClientManager.hpp"
#include "cmd/CommandManager.hpp"
#include "password/APassword.hpp"
#include "password/PasswordManager.hpp"

#include <string>

class Server
{
  public:
    Server(unsigned short port, std::string passwordString);
    ~Server();

    unsigned short getPort() const { return port; }

    void           start();

  private:
    int             socket_fd;
    unsigned short  port;
    APassword       password;

    PasswordManager passwordManager;
    CommandManager *commandHandler;
    ClientManager  *clientManager;
};

#endif // !SERVER_HPP
