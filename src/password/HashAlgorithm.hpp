#ifndef HASH_ALGORITHM_HPP
#define HASH_ALGORITHM_HPP

#include <string>
#include <stdint.h>

class HashAlgorithm
{
  public:
    virtual uint64_t hash(const std::string &);
};

#endif // !HASH_ALGORITHM_HPP
