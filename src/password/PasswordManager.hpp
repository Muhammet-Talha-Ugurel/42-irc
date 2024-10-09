#ifndef PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_HPP

#include "APassword.hpp"
#include "HashAlgorithm.hpp"

#include <string>

#define SALT_LENGTH 8

class PasswordManager
{
  public:
    PasswordManager(const HashAlgorithm *alg);
    ~PasswordManager();
    PasswordManager(const PasswordManager &other);

    bool            validate(const std::string &input, const APassword &target);

    const APassword createPassword(std::string password) const;

  private:
    std::string   generateSalt() const;

    const HashAlgorithm *algorithm;
};

#endif // !PASSWORD_MANAGER_HPP