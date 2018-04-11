#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "simplecrypt.h"
#include <QRandomGenerator>

class Cryptography : public SimpleCrypt
{
    QRandomGenerator generator;
    SimpleCrypt simple;
public:
    Cryptography();

protected:
    int seed;
    quint64 key;
    QString encryptString(QString strIn);
    QString decryptString(QString strIn);
    int generateRandom();
};

#endif // CRYPTOGRAPHY_H
