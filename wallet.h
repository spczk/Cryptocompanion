#ifndef WALLET_H
#define WALLET_H

#include <QVector>
#include "cryptocurrency.h"

class Wallet
{
    QString name;
    QVector<QString> publicKey;
    QVector<QString> passPhrase;
    QVector<QString> privateKey;
    QVector<QString> wordCode;
    QVector<QString> address;
    Cryptocurrency Crypto;
    QVector<QString> cryptocurrencyName;
public:
    Wallet();
};

#endif // WALLET_H
