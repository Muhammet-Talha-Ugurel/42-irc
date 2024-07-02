#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include "client.hpp"

class Server {
public:
    Server(int port, const std::string& password);
    void run();

private:
    void handle_client(int client_socket);
    void handle_command(Client* client, const std::string& command);
    void handle_nick(Client* client, const std::string& nickname);
    void handle_user(Client* client, const std::string& username, const std::string& hostname, const std::string& servername, const std::string& realname);
    void handle_join(Client* client, const std::string& channel);
    void handle_part(Client* client, const std::string& channel);
    void handle_privmsg(Client* client, const std::string& target, const std::string& message);
    void send_message_to_channel(const std::string& channel, const std::string& message, Client* sender);

    int server_fd;
    int port;
    std::string password;
    std::map<int, Client*> clients;
    std::map<std::string, std::vector<Client*> > channels;
};

#endif // SERVER_HPP
