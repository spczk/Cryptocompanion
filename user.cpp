#include "user.h"

User::User()
{
    firstName = "Jan";
    lastName ="Kowalski";
    password = "test";
}

User::~User()
{
    //delete user;
}

void User::setFirstName(QString fnameIn)
{
    firstName=fnameIn;
}

void User::setLastName(QString lnameIn)
{
    lastName=lnameIn;
}

void User::setPassword(QString passwordIn)
{
    password=passwordIn;
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

void User::printInfo()
{
    //std::cout << firstName << " " << lastName << " " << password << std::endl;
}

void User::printName()
{
    //std::cout << firstName << " " << lastName << std::endl;
}
