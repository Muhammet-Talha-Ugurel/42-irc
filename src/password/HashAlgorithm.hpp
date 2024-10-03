#ifndef HASH_ALGORITHM_HPP
#define HASH_ALGORITHM_HPP

#include <cstdint>
#include <string>

class HashAlgorithm
{
  public:
    virtual uint64_t hash(const std::string &) const;
};

#endif // !HASH_ALGORITHM_HPP