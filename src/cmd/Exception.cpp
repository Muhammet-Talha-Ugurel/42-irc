#include "Commands.hpp"

void Exception::execute(Client *c, const Server &server)
{
  (void)server;
  c->receiveMessage(message);
}

bool Exception::canExecute(Client *c, const Server &server)
{
  (void)server;
  (void)c;
  return true;
}

void Exception::execute(const Client *c, const Server &s) { execute(const_cast<Client *>(c), s); }

bool Exception::canExecute(const Client *c, const Server &s)
{
  return canExecute(const_cast<Client *>(c), s);
}
