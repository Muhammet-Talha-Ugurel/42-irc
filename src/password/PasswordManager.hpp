#ifndef PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_HPP

#include "HashAlgorithm.hpp"
#include "Password.hpp"

#include <string>

#define SALT_LENGTH 8

class PasswordManager
{
  public:
    PasswordManager(const HashAlgorithm *alg);
    ~PasswordManager();
    PasswordManager(const PasswordManager &other);

    static PasswordManager *getInstance();

    void setAlgorithm(const HashAlgorithm *algorithm) { this->algorithm = algorithm; };
    const HashAlgorithm *getAlgorithm() const { return algorithm; };

    bool                 validate(const std::string &input, const Password *target);

    const Password       createPassword(std::string password);

  private:
    PasswordManager() {};
    std::string          generateSalt() const;

    const HashAlgorithm *algorithm;
};

#endif // !PASSWORD_MANAGER_HPP