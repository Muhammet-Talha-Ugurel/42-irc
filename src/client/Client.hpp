#ifndef CLIENT_HPP

#define CLIENT_HPP

#include <string>
class Client
{
  public:
    Client(const Client &);
    ~Client();
    Client(unsigned long ipv4, unsigned long ipv6, unsigned long port, const std::string &);

    unsigned long      getIpv4();
    unsigned long      getIpv6();
    unsigned long      getPort();

    const std::string &getNickname() const;
    void               setNickname(const std::string &);

  private:
    Client();
    unsigned long  ipv4;
    unsigned long  ipv6;
    unsigned short port;
    

    std::string    nickname;
};

#endif // !CLIENT_HPP