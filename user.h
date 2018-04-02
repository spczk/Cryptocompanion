#ifndef USER_H
#define USER_H

#include <QString>

class User
{
    QString firstName;
    QString lastName;
    QString password;
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
