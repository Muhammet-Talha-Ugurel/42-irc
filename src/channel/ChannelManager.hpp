#ifndef CHANNEL_MANAGER_HPP

#define CHANNEL_MANAGER_HPP

#include "Channel.hpp"

#include <map>

class ChannelManager
{
  public:
    ~ChannelManager();
    ChannelManager(ChannelManager &channelManager);

    ChannelManager           &getInstance();

    void                      addChannel(const Channel &);
    void                      removeChannel(const Channel *);

    const Channel            *getChannelByName(const std::string &);

    std::set<const Channel *> getChannelsByIsPublic(bool);

  private:
    ChannelManager();
    std::map<std::string, Channel> _channels;
};

#endif // !CHANNEL_MANAGER_HPP