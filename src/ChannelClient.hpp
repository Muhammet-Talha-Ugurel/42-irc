#ifndef CHANNELCLIENT_HPP

#define CHANNELCLIENT_HPP

#include "Client.hpp"

#include <locale>

class ChannelClient
{
  public:
    ChannelClient();
    ChannelClient(ChannelClient &);
    ~ChannelClient();

  private:
    Client        &_client;
    std::time_base join_time;
    std::time_base exit_time;
};

#endif // !CHANNELCLIENT_HPP