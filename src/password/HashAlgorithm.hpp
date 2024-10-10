#ifndef HASH_ALGORITHM_HPP
#define HASH_ALGORITHM_HPP

#include <stdint.h>
#include <string>

class HashAlgorithm
{
  public:
    virtual uint64_t hash(const std::string &) const = 0;
};

#endif // !HASH_ALGORITHM_HPP
