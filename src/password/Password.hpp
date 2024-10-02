#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include "APassword.hpp"

#include <cstdint>
#include <string>

class Password : public APassword
{
  public:
    Password(uint64_t hash, const std::string &salt);
    ~Password();
    Password(const Password &other);

    const uint64_t    getHash() const;
    const std::string getSalt() const;

    bool              exists() { return true; };

  private:
    uint64_t    _hash;
    std::string _salt;
};

#endif // !PASSWORD_HPP