#include "ChannelManager.hpp"

#include <stdexcept>

ChannelManager::ChannelManager() {}

ChannelManager::~ChannelManager() {}

ChannelManager &ChannelManager::getInstance()
{
		static ChannelManager instance;
		return instance;
}

void ChannelManager::addChannel(const Channel &channel)
{
		(void)channel;
		if (this->_channels.find(channel.getName()) == this->_channels.end())
				this->_channels.at(channel.getName()) = channel;
		else
				throw std::runtime_error("Channel already exists");
}

void ChannelManager::removeChannel(const Channel *channel)
{
		this->_channels.erase(channel->getName());
}

const Channel *ChannelManager::getChannelByName(const std::string &name)
{
		try {
				return &this->_channels.at(name);
		} catch (...) {
				return 0x00;
		}
}

std::set<const Channel *> ChannelManager::getChannelsByIsPublic(bool isPublic)
{
		std::set<const Channel *>                channels;
		std::map<std::string, Channel>::iterator it;

		for (it = this->_channels.begin(); it != this->_channels.end(); ++it) {
				if (it->second.isPrivate() == isPublic)
						channels.insert(&it->second);
		}

		return channels;
}
