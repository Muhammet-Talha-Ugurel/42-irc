#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include "Client.hpp"

#include <map>
#include <poll.h>
#include <set>
#include <vector>

class ClientManager
{
  private:
    ClientManager();

    std::set<Client>                       _clients;
    std::map<const User *, const Client *> _clientsByUser;
    std::map<const int, const Client *>    _clientsByFd;
    class UserManager                     *userManager;
    class ChannelManager                  *channelManager;

    void                                   deleteClient(const Client &);
    const Client                          *updateClient(const Client *src, const Client &dst);

  public:
    ClientManager(const ClientManager &);
    ClientManager &operator=(const ClientManager &);
    ~ClientManager();

    std::set<Client>                 &getClients() { return _clients; };

    static ClientManager             &getInstance();

    const UserManager                *getUserManager();

    const Client                     *createClient(const Client &);
    void                              allowClient(const Client *);

    const Client                     *updateClientByNickname(const std::string &, const Client &);
    const Client                     *updateClientByIpv4(const unsigned long, const Client &);
    const Client                     *updateClientByPort(const unsigned long, const Client &);
    const Client                     *updateClientByUser(const User *, const Client &);
    const Client                     *updateClientByPollfd(const pollfd, const Client &);

    const Client                     *findClientByNickname(const std::string &) const;
    const Client                     *findClientByIpv4(const unsigned long) const;
    const Client                     *findClientByPort(const unsigned long) const;
    const Client                     *findClientByUser(const User *) const;
    const Client                     *findClientByPollfd(const pollfd) const;

    const std::vector<const Client *> findClientsByUsers(const std::set<const User *> &) const;

    void                              deleteClientByIpv4(const unsigned long);
    void                              deleteClientByPort(const unsigned long);
    void                              deleteClientByNickname(const std::string &);
    void                              deleteClientByUser(const User *);
    void                              deleteClientByPollfd(const pollfd);
};

#endif // CLIENT_MANAGER_HPP
