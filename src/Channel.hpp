#ifndef CHANNEL_HPP

#define CHANNEL_HPP

#include "ChannelClient.hpp"
#include "Client.hpp"
#include "user/UserCommand.hpp"

#include <string>
#include <vector>

class Channel
{
  public:
    Channel(std::string name);
    Channel(Channel &channel);
    ~Channel();

    void                         add_client(Client *);
    void                         remove_client(Client *);
    std::vector<ChannelClient *> get_clients();

    void                         publish_message(std::string);
    void                         execute_command(UserCommand);

  private:
    std::string                  name;
    std::vector<ChannelClient *> clients;
};

#endif // !CHANNEL_HPP