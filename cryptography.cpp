#include "cryptography.h"

Cryptography::Cryptography()
{
    generator = *QRandomGenerator::system();
//    key = generator.generate64();
//    *keyptr = key;
//    SimpleCrypt simple(key);
    //qInfo() << key;
    //simple.setKey(key);
//    seed = generator.generate64();

}

//Cryptography::Cryptography(quint64 keyIn)
//{
//    generator = *QRandomGenerator::system();
//    key = keyIn;
//    SimpleCrypt simple(key);
////    seed = generator.generate64();

//}


quint64 generateKey()
{
   QRandomGenerator generator = *QRandomGenerator::system();
    return generator.generate64();
}

//QString Cryptography::encryptString(QString strIn)
//{
//    return simple.encryptToString(strIn);
//}

//QString Cryptography::decryptString(QString strIn)
//{
//    return simple.decryptToString(strIn);
//}


//quint64 Cryptography::getKey()
//{
//    return key;
//}
