#include "ClientManager.hpp"
#include "Client.hpp"

ClientManager::ClientManager() : userManager(UserManager::INSTANCE)
{
	_clients = std::set<Client *>();
}

ClientManager::ClientManager(const ClientManager &)
{
}

ClientManager::~ClientManager()
{
}

const ClientManager ClientManager::INSTANCE = ClientManager();

const Client *ClientManager::createClient(const Client &toCreate) const
{
	const Client *cl = new Client(toCreate);
	_clients.insert(cl);
	return cl;
}

const Client *ClientManager::updateClient(const Client &client)
{

	return &client;
}

