#ifndef USER_H
#define USER_H

#include <QString>
#include "cryptography.h"

class User : public Cryptography
{
    QString firstName;
    QString lastName;
    QString password;
    quint64 key;
public:

    User();
    User(quint64 keyIn,QString firstNameIn, QString lastNameIn, QString passwordIn);
    User(QString firstNameIn, QString lastNameIn, QString passwordIn);
    User(quint64 key);
    ~User();
    void setKey(quint64 keyIn);
    void setFirstName(QString fnameIn);
    void setLastName(QString lnameIn);
    void setPassword(QString passwordIn);
    QString getFirstName();
    QString getLastName();
    QString getPassword();
    quint64 getKey();
    QString getEncryptedString(QString strIn);
    QString getDecryptedString(QString strIn);
    void printInfo();
    void printName();
};

#endif // USER_H
