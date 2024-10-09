#include "Server.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{

  if (argc != 3) {
      std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
      return 1;
    }

  Server server = Server(atoi(argv[0]), argv[1]);
  server.start();
}