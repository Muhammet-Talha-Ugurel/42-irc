#ifndef PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_HPP

#include "HashAlgorithm.hpp"
#include "Password.hpp"

#include <string>
#include <vector>

#define SALT_LENGTH 8

class PasswordManager
{
  public:
    PasswordManager(const HashAlgorithm *alg);
    ~PasswordManager();
    PasswordManager(const PasswordManager &other);

    bool            validate(const std::string &input, const Password *target);

    const Password *createPassword(std::string password);
    void            deletePassword(Password *password);

  private:
    std::string             generateSalt() const;
    std::vector<Password *> _passwords;

    const HashAlgorithm    *algorithm;
};

#endif // !PASSWORD_MANAGER_HPP