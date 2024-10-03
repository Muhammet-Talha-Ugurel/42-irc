#include "Server.hpp"

#include "password/DJB2HashAlgorithm.hpp"
#include "password/PasswordManager.hpp"

#include <string>

Server::Server(unsigned short port, std::string passwordString)
    : port(port), passwordManager(PasswordManager(DJB2Hash()))
{
  password = passwordManager.createPassword(passwordString);
}