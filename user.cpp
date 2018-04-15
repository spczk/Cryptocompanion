#include "user.h"

User::User()
{
    firstName = "Jan";
    lastName ="Kowalski";
    password = "test";
   // Cryptography crypto;
}
User::User(QString firstNameIn, QString lastNameIn, QString passwordIn)
{
  firstName = firstNameIn;
  lastName = lastNameIn;
  password = passwordIn;
 // Cryptography crypto;
}

User::User(quint64 key)
{
    firstName = "Jan";
    lastName ="Kowalski";
    password = "test";
 //   Cryptography crypto(key);
}

User::~User()
{
    //delete user;
}

User::User(quint64 keyIn,QString firstNameIn, QString lastNameIn, QString passwordIn)
{
  firstName = firstNameIn;
  lastName = lastNameIn;
  password = passwordIn;
  key = keyIn;
 // Cryptography crypto;
}

void User::setKey(quint64 keyIn)
{
    key = keyIn;
}

void User::setFirstName(QString fnameIn)
{
    firstName = fnameIn;
}

void User::setLastName(QString lnameIn)
{
    lastName = lnameIn;
}

void User::setPassword(QString passwordIn)
{
    password = passwordIn;
}

void User::setRecoveryCode(QString recoveryCodeIn)
{
    recoveryCode = recoveryCodeIn;
}

QString User::getFirstName()
{
    return firstName;
}

QString User::getLastName()
{
    return lastName;
}

QString User::getPassword()
{
    return password;
}

quint64 User::getKey()
{
    return key;
}

QString User::getRecoveryCode()
{
    return recoveryCode;
}


//QString User::getEncryptedString(QString strIn)
//{
//    return this->encryptString(strIn);
//}

//QString User::getDecryptedString(QString strIn)
//{
//    return this->decryptString(strIn);
//}

void User::printInfo()
{
    //std::cout << firstName << " " << lastName << " " << password << std::endl;
}

void User::printName()
{
    //std::cout << firstName << " " << lastName << std::endl;
}
