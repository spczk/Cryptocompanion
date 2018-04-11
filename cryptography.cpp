#include "cryptography.h"

Cryptography::Cryptography()
{
    generator = *QRandomGenerator::system();
//    seed = generator.generate64();
    key = generator.generate64();
}

/*int generateRandom()
{
    return generator.generate64();
}*/
