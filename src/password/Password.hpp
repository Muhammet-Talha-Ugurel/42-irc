#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <stdint.h>
#include <string>

class Password
{
  public:
    Password(uint64_t hash, const std::string &salt) : _hash(hash), _salt(salt) {};
    Password(const Password &other) : _hash(other._hash), _salt(other._salt) {};
    ~Password() {};

    bool operator==(const Password &other) const
    {
      return _hash == other._hash && _salt == other._salt;
    };

    uint64_t          getHash() const { return _hash; };
    const std::string getSalt() const { return _salt; };

    static Password   nan() { return Password(0, ""); };

  private:
    uint64_t    _hash;
    std::string _salt;
};

#endif // !PASSWORD_HPP
