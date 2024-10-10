#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include "Client.hpp"

#include <map>
#include <set>
#include <vector>

class ClientManager
{
  private:
    ClientManager();

    std::set<Client>                       _clients;
    std::map<const User *, const Client *> _clientsByUser;
    const class UserManager               *userManager;

    void                                   deleteClient(const Client &);

  public:
    ClientManager(const ClientManager &);
    ClientManager &operator=(const ClientManager &);
    ~ClientManager();

    static ClientManager             &getInstance();

    const Client                     *createClient(const Client &);
    const Client                     *updateClientByNickname(const std::string &, const Client &);

    void                              deleteClientByIpv4(const unsigned long);
    void                              deleteClientByIpv6(const unsigned long);
    void                              deleteClientByPort(const unsigned long);
    void                              deleteClientByNickname(const std::string &);

    const Client                     *findClientByNickname(const std::string &) const;
    const Client                     *findClientByIpv4(const unsigned long) const;
    const Client                     *findClientByIpv6(const unsigned long) const;
    const Client                     *findClientByPort(const unsigned long) const;
    const Client                     *findClientByUser(const User *) const;
    const std::vector<const Client *> findClientsByUsers(const std::set<const User *> &) const;
};

#endif // CLIENT_MANAGER_HPP
