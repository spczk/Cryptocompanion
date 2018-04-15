#ifndef WALLET_H
#define WALLET_H

#include <QVector>
#include <QList>
#include <QVariant>
#include "cryptocurrency.h"

struct Wallet
{


public:
    Wallet();

    QString name;
    QString address;
    QString publicKey;
    QString passPhrase;
    QString privateKey;
    QString wordCode;
    QString cryptocurrencyName;


   bool operator ==(const Wallet &other) const
    {
        return name == other.name && address == other.address && publicKey == other.publicKey && privateKey == other.privateKey && passPhrase == other.passPhrase && wordCode == other.wordCode && cryptocurrencyName == other.cryptocurrencyName ;
    }

};

#endif // WALLET_H
