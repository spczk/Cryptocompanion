#ifndef USER_H
#define USER_H

#include <QString>

class User
{
    QString firstName;
    QString lastName;
    QString password;
    quint64 key;
    QString recoveryCode;
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
    void setRecoveryCode(QString recoveryCodeIn);
    QString getFirstName();
    QString getLastName();
    QString getPassword();
    quint64 getKey();
    QString getRecoveryCode();
    QString getEncryptedString(QString strIn);
    QString getDecryptedString(QString strIn);
};

#endif // USER_H
