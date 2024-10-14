#include "Server.hpp"

#include "channel/ChannelManager.hpp"
#include "cmd/ACommand.hpp"
#include "password/DJB2HashAlgorithm.hpp"
#include "password/PasswordManager.hpp"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <string>
#include <sys/socket.h>

Server::Server(unsigned short port, std::string passwordString)
    : _port(port), _command_handler(&CommandManager::getInstance()),
      _client_manager(&ClientManager::getInstance()),
      _channel_manager(&ChannelManager::getInstance()),
      _user_manager(&UserManager::getInstance())
{
  _password_manager = PasswordManager::getInstance(),
  _password_manager->setAlgorithm(DJB2HashAlgorithm::getInstance());
  _password  = _password_manager->createPassword(passwordString);
  _socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  int opt    = 1;
  if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
      perror("setsockopt");
      exit(EXIT_FAILURE);
    }
  struct sockaddr_in address;
  address.sin_family      = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port        = htons(port);

  if (bind(_socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
      perror("bind failed");
      exit(EXIT_FAILURE);
    }

  if (listen(_socket_fd, 10) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
    }

  if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1) {
      perror("fcntl");
      exit(EXIT_FAILURE);
    }
}

Server::~Server() { delete _password_manager; }

void Server::start()
{
  struct pollfd poll_fds[100];

  int           nfds = 1;
  poll_fds[0].fd     = _socket_fd;
  poll_fds[0].events = POLLIN;

  while (true) {
      int poll_count = poll(poll_fds, nfds, -1);

      if (poll_count == -1) {
          perror("poll");
          exit(EXIT_FAILURE);
        }

      for (int i = 0; i < nfds; ++i) {
          if (poll_fds[i].revents & POLLIN) {
              if (poll_fds[i].fd == _socket_fd) {
                  int                new_socket;

                  struct sockaddr_in address;
                  socklen_t          addrlen = sizeof(address);

                  new_socket = accept(_socket_fd, (struct sockaddr *)&address, &addrlen);
                  if (new_socket < 0) {
                      perror("accept");
                      exit(EXIT_FAILURE);
                    }
                  fcntl(new_socket, F_SETFL, O_NONBLOCK);
                  poll_fds[nfds].fd     = new_socket;
                  poll_fds[nfds].events = POLLIN;
                  _client_manager->createClient(
                      Client(address.sin_addr.s_addr, address.sin_port, poll_fds[nfds].fd)
                  );
                  nfds++;
                }
              else {
                  const Client *client = _client_manager->findClientByPollfd(poll_fds[i]);
                  const char   *buffer = client->getBuffer();
                  int bytes_received = recv(poll_fds[i].fd, (void *)buffer, 1024 * sizeof(char), 0);
                  std::string buffer_str(buffer);
                  std::cout << "Received: " << buffer_str << std::endl;
                  client->flushBuffer();

                  if (bytes_received > 0 && buffer_str.length() > 0) {
                      std::vector<ACommand *> commands = _command_handler->parseCommand(buffer_str);

                      for (std::vector<ACommand *>::iterator it = commands.begin();
                           it != commands.end(); ++it)
                        {
                          if ((*it)->canExecute(client, *this)) {
                              (*it)->execute(client, *this);
                            }
                          delete *it;
                        }
                      ;
                    }
                  else if (bytes_received == 0) {
                      std::cout << "Client disconnected." << std::endl;
                      poll_fds[i] = poll_fds[nfds - 1];
                      nfds--;
                    }
                  else if (bytes_received == -1) {
                      continue;
                    }
                  else {
                      perror("recv");
                    }
                }
            }
        }
    }
}

std::string Server::respond(std::string code, const Client *client, std::string message)
{
  std::string response = code + " " + client->getNickname() + " " + message + "\r\n";
  return response;
}

std::string Server::respond(std::string code, const Client *client, std::string message) const
{
  std::string response = code + " " + client->getNickname() + " " + message + "\r\n";
  return response;
}
