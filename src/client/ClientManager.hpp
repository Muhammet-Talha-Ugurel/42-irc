#ifndef CLIENT_MANAGER_HPP

#define CLIENT_MANAGER_HPP

#include "Client.hpp"
#include "../user/UserManager.hpp"

#include <set>

class ClientManager
{
  private:
    std::set<Client *> _clients;
    UserManager userManager;

  public:
    ClientManager();
    ClientManager(const ClientManager &);
    ~ClientManager();

    static const ClientManager INSTANCE;

    const Client            *createClient(const Client &) const;
    const Client            *updateClient(const Client &);

    void                     deleteClientByIpv4(const unsigned long);
    void                     deleteClientByIpv6(const unsigned long);
    void                     deleteClientByPort(const unsigned long);
    void                     deleteClientByNickname(const std::string &);

    std::set<const Client *> findAllClientByNickname(const std::string &);
    std::set<const Client *> findAllClientByClientname(const std::string &);
};


#endif // !CLIENT_MANAGER_HPP