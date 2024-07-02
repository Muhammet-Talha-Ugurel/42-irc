#ifndef SERVER_HPP

#define SERVER_HPP

#include "Channel.hpp"
#include "Client.hpp"

#include <string>
#include <vector>

class Server
{
  public:
    Server(std::string name);
    ~Server();
    void                   addChannel(Channel *channel);
    void                   removeChannel(Channel *channel);
    void                   addClient(Client *client);
    void                   removeClient(Client *client);
    std::vector<Channel *> getChannels() noexcept;
    std::vector<Client *>  getClients() noexcept;

  private:
	std::vector<Channel *>	_channels;
	std::vector<Channel *>	_clients;
};

#endif // !SERVER_HPP