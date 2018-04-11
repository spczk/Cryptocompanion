#ifndef USER_H
#define USER_H

#include <QString>
#include "cryptography.h"

class User : public Cryptography
{
    QString firstName;
    QString lastName;
    QString password;
    Cryptography crypto;
public:

    User();
    ~User();
    void setFirstName(QString fnameIn);
    void setLastName(QString lnameIn);
    void setPassword(QString passwordIn);
    QString getFirstName();
    QString getLastName();
    QString getPassword();
    void printInfo();
    void printName();
};

#endif // USER_H
