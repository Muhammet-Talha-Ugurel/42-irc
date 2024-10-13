#include "PasswordManager.hpp"

#include "HashAlgorithm.hpp"
#include "Password.hpp"

#include <cstdlib>
#include <cstring>
#include <ctime>

PasswordManager::PasswordManager(const HashAlgorithm *algorithm) : algorithm(algorithm)
{
  srand(time(0));
}

PasswordManager::~PasswordManager()
{
  for (std::vector<Password *>::iterator it = this->_passwords.begin();
       it != this->_passwords.end(); ++it)
    {
      delete *it;
    }
}

PasswordManager::PasswordManager(const PasswordManager &other) : algorithm(other.algorithm) {}

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

const Password *PasswordManager::createPassword(const std::string input)
{
  std::string salt = generateSalt();
  std::string pass = input + salt;
  uint64_t    hash = algorithm->hash(pass);

  Password   *p    = new Password(hash, salt);
  this->_passwords.push_back(p);

  return p;
}

void PasswordManager::deletePassword(Password *password)
{
  for (std::vector<Password *>::iterator it = this->_passwords.begin();
       it != this->_passwords.end(); ++it)
    {
      if (*it == password) {
          this->_passwords.erase(it);
          delete password;
          break;
        }
    }
}

bool PasswordManager::validate(const std::string &input, const Password *passwd)
{
  if (passwd == 0x00 || *passwd == Password::nan()) {
      return true;
    }
  return algorithm->hash(input + passwd->getSalt()) == passwd->getHash();
}
