#ifndef DJB2_HASH_HPP
#define DJB2_HASH_HPP

#include "HashAlgorithm.hpp"
#include <cstdint>
#include <string>

class DJB2Hash : public HashAlgorithm
{
  public:
    uint64_t hash(std::string str)
    {
      uint64_t hash = 5381L;
      int      c;
      for (size_t i = 0; i < str.length(); ++i) {
          c    = str[i];
          hash = ((hash << 5) + hash) + c;
        }
      return hash;
    }
};

#endif // !DJB2_HASH_HPP