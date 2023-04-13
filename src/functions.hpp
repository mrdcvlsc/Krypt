#ifndef KRYPT_FUNCTIONS_HPP
#define KRYPT_FUNCTIONS_HPP

#include "types.hpp"
#include <iostream>

namespace Krypt {
    inline Bytes xtime(Bytes b); // multiply on x
    inline void SubDWordBytes(Bytes *a);
    inline void RotDWord(Bytes *a);
    inline void XorDWords(Bytes *a, Bytes *b, Bytes *dest);
    inline void XorBlocks(unsigned char *a, unsigned char *b, unsigned char *c, unsigned int len);
    inline void XorAesBlock(unsigned char *a, unsigned char *b, unsigned char *result);

    void Rcon(Bytes *a, int n);
    void printHexArray(unsigned char a[], size_t n);
    void printHexVector(const std::vector<unsigned char> &a);
    std::vector<unsigned char> ArrayToVector(unsigned char *a, unsigned char len);
    unsigned char *VectorToArray(const std::vector<unsigned char> &a);
} // namespace Krypt

#include "functions.cpp"

#endif