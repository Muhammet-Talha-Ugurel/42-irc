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
    const class UserManager               *userManager;

    void                                   deleteClient(const Client &);

  public:
    ClientManager(const ClientManager &);
    ClientManager &operator=(const ClientManager &);
    ~ClientManager();

    static ClientManager             &getInstance();

    const Client                     *createClient(const Client &);
    const Client                     *updateClientByNickname(const std::string &, const Client &);

    // const std::vector<

    const Client                     *findClientByNickname(const std::string &) const;
    const Client                     *findClientByIpv4(const unsigned long) const;
    const Client                     *findClientByPort(const unsigned long) const;
    const Client                     *findClientByUser(const User *) const;
    const std::vector<const Client *> findClientsByUsers(const std::set<const User *> &) const;
    const Client                     *findClientByPollfd(const pollfd) const;

    void                              deleteClientByIpv4(const unsigned long);
    void                              deleteClientByPort(const unsigned long);
    void                              deleteClientByNickname(const std::string &);
    void                              deleteClientByUser(const User *);
    void                              deleteClientByPollfd(const pollfd);
};

#endif // CLIENT_MANAGER_HPP
