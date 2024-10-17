#include "Server.hpp"

#include "channel/ChannelManager.hpp"
#include "cmd/ACommand.hpp"
#include "password/DJB2HashAlgorithm.hpp"
#include "password/PasswordManager.hpp"

#include <algorithm>
#include <arpa/inet.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(unsigned short port, std::string passwordString)
    : _port(port), _command_handler(&CommandManager::getInstance()), _client_manager(&ClientManager::getInstance()),
      _channel_manager(&ChannelManager::getInstance()), _user_manager(&UserManager::getInstance())
{
  _password_manager = PasswordManager::getInstance(), _password_manager->setAlgorithm(DJB2HashAlgorithm::getInstance());
  _password         = _password_manager->createPassword(passwordString);
  _socket_fd        = socket(AF_INET, SOCK_STREAM, 0);

  int opt           = 1;
  if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in address;
  address.sin_family      = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port        = htons(port);

  if (bind(_socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(_socket_fd, 10) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1)
  {
    perror("fcntl");
    exit(EXIT_FAILURE);
  }
}

Server::~Server() { close(_socket_fd); }

void Server::start()
{
  struct pollfd poll_fds[100];

  int           nfds = 1;
  poll_fds[0].fd     = _socket_fd;
  poll_fds[0].events = POLLIN;

  while (true)
  {
    int poll_count = poll(poll_fds, nfds, -1);

    if (poll_count == -1)
    {
      perror("poll");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nfds; ++i)
    {
      if (poll_fds[i].revents & POLLIN)
      {
        if (poll_fds[i].fd == _socket_fd)
        {
          int                new_socket;

          struct sockaddr_in address;
          socklen_t          addrlen = sizeof(address);

          new_socket                 = accept(_socket_fd, (struct sockaddr *)&address, &addrlen);
          if (new_socket < 0)
          {
            perror("accept");
            exit(EXIT_FAILURE);
          }
          fcntl(new_socket, F_SETFL, O_NONBLOCK);
          poll_fds[nfds].fd     = new_socket;
          poll_fds[nfds].events = POLLIN;
          _client_manager->createClient(Client(address.sin_addr.s_addr, address.sin_port, poll_fds[nfds].fd));
          nfds++;
        }
        else
        {
          Client *client = const_cast<Client *>(_client_manager->findClientByPollfd(poll_fds[i]));
          if (client == 0x00)
            continue;

          char buffer[1024];
          int  bytes_received = recv(poll_fds[i].fd, buffer, sizeof(buffer), 0);

          if (bytes_received > 0)
          {
            client->appendToBuffer(buffer, bytes_received);

            std::string &clientBuffer = client->getBuffer();
            size_t       newlinePos;

            while ((newlinePos = clientBuffer.find('\n')) != std::string::npos)
            {
              std::string commandLine = clientBuffer.substr(0, newlinePos + 1);

              client->clearBufferUpTo(newlinePos + 1);

              commandLine.erase(std::remove(commandLine.begin(), commandLine.end(), '\r'), commandLine.end());
              commandLine.erase(std::remove(commandLine.begin(), commandLine.end(), '\n'), commandLine.end());

              std::cout << "Received command: " << commandLine << std::endl;

              std::vector<ACommand *> commands = _command_handler->parseCommand(commandLine);

              for (std::vector<ACommand *>::iterator it = commands.begin(); it != commands.end(); ++it)
              {
                if ((*it)->canExecute(client, *this))
                {
                  (*it)->execute(client, *this);
                }
                delete *it;
              }
            }
          }
          else if (bytes_received == 0)
          {
            std::cout << "Client disconnected." << std::endl;
            _client_manager->deleteClientByPollfd(poll_fds[i]);
            poll_fds[i] = poll_fds[nfds - 1];
            nfds--;
            i--;
          }
          else if (bytes_received == -1)
          {
            if (errno != EWOULDBLOCK && errno != EAGAIN)
            {
              perror("recv");
              _client_manager->deleteClientByPollfd(poll_fds[i]);
              poll_fds[i] = poll_fds[nfds - 1];
              nfds--;
              i--;
            }
          }
        }
      }
    }
  }
}

std::string Server::respond(std::string code, const Client *client, std::string message)
{
  std::string response = ": " + code + " " + client->getNickname() + " " + message;
  std::cout << response << std::endl;
  return response;
}

std::string Server::respond(std::string code, const Client *client, std::string message) const
{
  std::string response = ": " + code + " " + client->getNickname() + " " + message;
  std::cout << response << std::endl;
  return response;
}
