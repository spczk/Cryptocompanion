#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "simplecrypt.h"
#include <QRandomGenerator>

class Cryptography
{
    QRandomGenerator generator;
    SimpleCrypt simple;
public:
    Cryptography();
    Cryptography(quint64 keyIn);
    quint64 *keyptr;

protected:
    int seed;
    quint64 key;
    QString encryptString(QString strIn);
    QString decryptString(QString strIn);
    quint64 generateKey();
    quint64 getKey();
};

#endif // CRYPTOGRAPHY_H
