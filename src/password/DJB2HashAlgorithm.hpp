#ifndef DJB2_HASH_HPP
#define DJB2_HASH_HPP

#include "HashAlgorithm.hpp"

#include <stdint.h>
#include <string>

class DJB2HashAlgorithm : public HashAlgorithm
{
  public:
    static const DJB2HashAlgorithm *getInstance()
    {
      static DJB2HashAlgorithm instance;
      return &instance;
    }

    uint64_t hash(const std::string &str) const
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
