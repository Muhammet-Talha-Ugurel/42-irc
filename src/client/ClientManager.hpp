#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include "Client.hpp"
#include "../user/UserManager.hpp"
#include <set>

class ClientManager
{
  private:
    std::set<Client> _clients;
    const UserManager &userManager;

    ClientManager();

  public:
    ClientManager(const ClientManager &);
    ClientManager &operator=(const ClientManager &);
    ~ClientManager();

    static ClientManager &getInstance();

    const Client *createClient(const Client &);
    const Client *updateClientByNickname(const std::string &, const Client &);

    void deleteClientByIpv4(const unsigned long);
    void deleteClientByIpv6(const unsigned long);
    void deleteClientByPort(const unsigned long);
    void deleteClientByNickname(const std::string &);

    const Client * findClientByNickname(const std::string &);
    const Client * findClientByIpv4(const unsigned long);
    const Client * findClientByIpv6(const unsigned long);
    const Client * findClientByPort(const unsigned long);
};

#endif // CLIENT_MANAGER_HPP
