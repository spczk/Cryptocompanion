#include "cryptography.h"

Cryptography::Cryptography()
{
    generator = *QRandomGenerator::system();
    key = generator.generate64();
    simple.setKey(key);
//    seed = generator.generate64();

}

/*int generateRandom()
{
    return generator.generate64();
}*/

