#include "Password.hpp"

Password::Password(uint64_t hash, const std::string &salt)
  : _hash(hash), _salt(salt)
{
}

Password::~Password()
{
}

Password::Password(const Password &other)
  : _hash(other._hash), _salt(other._salt)
{
}

uint64_t Password::getHash() const
{
  return _hash;
}

const std::string Password::getSalt() const
{
  return _salt;
}