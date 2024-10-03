#ifndef SERVER_HPP

#define SERVER_HPP

#include "Channel.hpp"
#include "Client.hpp"
#include "password/APassword.hpp"
#include "password/PasswordManager.hpp"

#include <set>
#include <string>

class Server
{
  public:
    Server(unsigned short port, std::string passwordString);
    ~Server();

    void                addChannel(Channel *channel);
    void                validateChannel(Channel *channel);
    void                removeChannel(Channel *channel);

    void                addClient(Client *client);
    void                validateClient(Client *client);
    void                removeClient(Client *client);

    std::set<Channel *> getChannels();
    std::set<Client *>  getClients();

  private:
    std::set<Channel *> _channels;
    std::set<Client *>  _clients;

    unsigned short      port;
    APassword           password;

    PasswordManager     passwordManager;
};

#endif // !SERVER_HPP
