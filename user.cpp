#include "user.h"

User::User()
{
    firstName = "Jan";
    lastName ="Kowalski";
    password = "test";
}
User::User(QString firstNameIn, QString lastNameIn, QString passwordIn)
{
  firstName = firstNameIn;
  lastName = lastNameIn;
  password = passwordIn;
}

User::~User()
{
}

User::User(quint64 keyIn,QString firstNameIn, QString lastNameIn, QString passwordIn)
{
  firstName = firstNameIn;
  lastName = lastNameIn;
  password = passwordIn;
  key = keyIn;
}

//get - gets the variable from user object
//set - sets the variable in user object

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


