#include "server.hpp"
#include <algorithm>
#include <sstream>

Server::Server(int port, const std::string& password) : port(port), password(password) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    fcntl(server_fd, F_SETFL, O_NONBLOCK);
}

void Server::run() {
    std::cout << "Server is listening on port " << port << std::endl;

    struct pollfd poll_fds[100];
    int nfds = 1;

    poll_fds[0].fd = server_fd;
    poll_fds[0].events = POLLIN;

    while (true) {
        int poll_count = poll(poll_fds, nfds, -1);

        if (poll_count == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nfds; ++i) {
            if (poll_fds[i].revents & POLLIN) {
                if (poll_fds[i].fd == server_fd) {
                    int new_socket;
                    struct sockaddr_in address;
                    socklen_t addrlen = sizeof(address);
                    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
                    if (new_socket < 0) {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }

                    fcntl(new_socket, F_SETFL, O_NONBLOCK);
                    poll_fds[nfds].fd = new_socket;
                    poll_fds[nfds].events = POLLIN;
                    nfds++;

                    clients[new_socket] = new Client(new_socket);
                } else {
                    handle_client(poll_fds[i].fd);
                }
            }
        }
    }
}

void Server::handle_client(int client_socket) {
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        close(client_socket);
        clients.erase(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    std::string command(buffer);
    handle_command(clients[client_socket], command);
}

void Server::handle_command(Client* client, const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "NICK") {
        std::string nickname;
        iss >> nickname;
        handle_nick(client, nickname);
    } else if (cmd == "JOIN") {
        std::string channel;
        iss >> channel;
        handle_join(client, channel);
    } else if (cmd == "PART") {
        std::string channel;
        iss >> channel;
        handle_part(client, channel);
    } else if (cmd == "PRIVMSG") {
        std::string target;
		std::string message;
        iss >> target;
        std::getline(iss, message);
        handle_privmsg(client, target, message);
    }
}

void Server::handle_nick(Client* client, const std::string& nickname) {
    client->set_nickname(nickname);
    std::string msg = "NICK " + nickname + "\r\n";
    send(client->get_socket(), msg.c_str(), msg.size(), 0);
}

void Server::handle_join(Client* client, const std::string& channel) {
    channels[channel].push_back(client);
    std::string msg = client->get_nickname() + " JOIN " + channel + "\r\n";
    send_message_to_channel(channel, msg, client);
}

void Server::handle_part(Client* client, const std::string& channel) {
    std::vector<Client*>& clients_in_channel = channels[channel];
    clients_in_channel.erase(std::remove(clients_in_channel.begin(), clients_in_channel.end(), client), clients_in_channel.end());
    std::string msg = client->get_nickname() + " PART " + channel + "\r\n";
    send_message_to_channel(channel, msg, client);
}

void Server::handle_privmsg(Client* client, const std::string& target, const std::string& message) {
    std::string msg = client->get_nickname() + " PRIVMSG " + target + " :" + message + "\r\n";
    send_message_to_channel(target, msg, client);
}

void Server::send_message_to_channel(const std::string& channel, const std::string& message, Client* sender) {
    std::vector<Client*>& clients_in_channel = channels[channel];
    for (size_t i = 0; i < clients_in_channel.size(); ++i) {
        if (clients_in_channel[i] != sender) {
            send(clients_in_channel[i]->get_socket(), message.c_str(), message.size(), 0);
        }
    }
}