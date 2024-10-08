#include "Server.hpp"

#include "client/Client.hpp"
#include "client/ClientManager.hpp"
#include "cmd/CommandHandler.hpp"
#include "password/DJB2HashAlgorithm.hpp"
#include "password/PasswordManager.hpp"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <string>
#include <sys/socket.h>

Server::Server(unsigned short port, std::string passwordString)
    : port(port), passwordManager(PasswordManager(DJB2Hash::getInstance()))
{
  password  = passwordManager.createPassword(passwordString);
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  

  int opt   = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
      perror("setsockopt");
      exit(EXIT_FAILURE);
    }
  struct sockaddr_in address;
  address.sin_family      = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port        = htons(port);

  if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
      perror("bind failed");
      exit(EXIT_FAILURE);
    }

  if (listen(socket_fd, 10) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
    }

  if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1) {
      perror("fcntl");
      exit(EXIT_FAILURE);
    }
}

Server::~Server()
{
  
}

void Server::start()
{
  struct pollfd   poll_fds[100];
  ClientManager  &cmg        = ClientManager::getInstance();
  CommandHandler &cmdHandler = CommandHandler::getInstance();

  int             nfds       = 1;

  poll_fds[0].fd             = socket_fd;
  poll_fds[0].events         = POLLIN;

  while (true) {
      int poll_count = poll(poll_fds, nfds, -1);

      if (poll_count == -1) {
          perror("poll");
          exit(EXIT_FAILURE);
        }

      for (int i = 0; i < nfds; ++i) {
          if (poll_fds[i].revents & POLLIN) {
              if (poll_fds[i].fd == socket_fd) {
                  int                new_socket;
                  struct sockaddr_in address;
                  socklen_t          addrlen = sizeof(address);
                  new_socket = accept(socket_fd, (struct sockaddr *)&address, &addrlen);
                  if (new_socket < 0) {
                      perror("accept");
                      exit(EXIT_FAILURE);
                    }

                  fcntl(new_socket, F_SETFL, O_NONBLOCK);
                  poll_fds[nfds].fd     = new_socket;
                  poll_fds[nfds].events = POLLIN;
                  nfds++;

                  cmg.createClient(Client(address.sin_addr.s_addr, 0, address.sin_port, ""));
                  // clients[new_socket] = new Client(new_socket);
                }
              else {
                  cmdHandler.parseCommand("test");
                }
            }
        }
    }
}