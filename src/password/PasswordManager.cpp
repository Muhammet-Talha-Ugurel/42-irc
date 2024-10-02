#include "PasswordManager.hpp"

#include "APassword.hpp"
#include "HashAlgorithm.hpp"
#include "Password.hpp"

#include <cstdlib>
#include <cstring>
#include <ctime>

PasswordManager::PasswordManager(HashAlgorithm algorithm) : algorithm(algorithm) { srand(time(0)); }

std::string PasswordManager::generateSalt() const
{
  const char *chars    = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const int   charsLen = strlen(chars);

  std::string salt;
  salt.reserve(SALT_LENGTH);

  for (int i = 0; i < SALT_LENGTH; ++i) {
      salt += chars[rand() % charsLen];
    }

  return salt;
}

const APassword PasswordManager::createPassword(const std::string input) const
{
  std::string salt = generateSalt();

  uint64_t    hash = algorithm.hash(input + salt);

  return Password(hash, salt);
}

bool PasswordManager::validate(const std::string &input, const APassword &passwd)
{
  const Password &ref  = dynamic_cast<const Password &>(passwd);

  uint64_t        eval = algorithm.hash(input + ref.getSalt());

  return eval == ref.getHash();
}
