#ifndef WALLET_H
#define WALLET_H

#include <QVector>
#include "cryptocurrency.h"

class Wallet
{


public:
    Wallet();

    QString name;
    QVector<QString> publicKey;
    QVector<QString> passPhrase;
    QVector<QString> privateKey;
    QVector<QString> wordCode;
    QVector<QString> address;
    Cryptocurrency Crypto;
    QVector<QString> cryptocurrencyName;


   bool operator ==(const Wallet &other) const
    {
        return name == other.name && address == other.address && publicKey == other.publicKey && privateKey == other.privateKey && passPhrase == other.passPhrase && wordCode == other.wordCode && cryptocurrencyName == other.cryptocurrencyName ;
    }

};

#endif // WALLET_H
