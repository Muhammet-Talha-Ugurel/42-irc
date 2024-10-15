#ifndef CHANNEL_MANAGER_HPP

#define CHANNEL_MANAGER_HPP

#include "Channel.hpp"

#include <map>

class ChannelManager
{
  public:
    ~ChannelManager();
    ChannelManager(ChannelManager &channelManager);

    static ChannelManager    &getInstance();

    void                      addChannel(const Channel &);
    void                      removeChannel(const Channel *);

    Channel                  *findChannelByName(const std::string &);

    std::set<const Channel *> findChannelsByIsPublic(bool);

    std::set<Channel *>       findChannelsByClient(Client *);

    void                      removeUserFromChannels(const User *);

  private:
    ChannelManager();
    std::map<std::string, Channel> _channels;
};

#endif // !CHANNEL_MANAGER_HPP