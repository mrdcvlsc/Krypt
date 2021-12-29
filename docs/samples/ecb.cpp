#include <iostream>
#include "../../src/Krypt.hpp"

using namespace Krypt;

#define KEYLEN 16
#define PLAINLEN 11

int main()
{
    unsigned char plain[] = {
        0x00, 0x1a, 0x22, 0xb3, 0x4c, 0x13, 0xb6, 0xbb,
        0xf0, 0x11, 0x2a
    };

    unsigned char AES128KEY[KEYLEN] = {
        0x00, 0xa2, 0xff, 0x3c, 0xd4, 0x11, 0x2e, 0x02,
        0x21, 0x2f, 0x54, 0xa7, 0xaf, 0xec, 0x01, 0x32
    };

    Mode::ECB<BlockCipher::AES,Padding::ANSI_X9_23> krypt(AES128KEY,KEYLEN);

    ByteArray cipher  = krypt.encrypt(plain,PLAINLEN);
    ByteArray recover = krypt.decrypt(cipher.array,cipher.length);

    std::cout << "Plain   : ";
    printHexArray(plain,PLAINLEN);

    std::cout << "Cipher  : ";
    printHexArray(cipher.array,cipher.length);

    std::cout << "Recover : ";
    printHexArray(recover.array,recover.length);

    return 0;
}

// compile using portable C++ code and looping
// g++ ecb.cpp -o ecb -O2

// compile using AES-NI [huge performance boost is AES-NI is supported]
// g++ ecb.cpp -o ecb -D USE_AESNI -O2 -maes