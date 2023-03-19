#ifndef KRYPT_FUNCTIONS_CPP
#define KRYPT_FUNCTIONS_CPP

#include "functions.hpp"

// here the DWORDS is formed from 4 continous elements from a starting index of an unsinged char* array or Bytes*.
// a DWORD or double-word occupies 32-bits in a memory.
// the term DWORD is usually used to represent bits inside the eax,edx,...r15d parts of an x86_64 cpu register which can contain 32 bits inside.  

namespace Krypt
{
    Bytes xtime(Bytes b)    // multiply on x
    {
        return (b << 1) ^ (((b >> 7) & 1) * 0x1b);
    }

    void SubDWordBytes(Bytes *a)
    {
        a[0] = sbox[a[0]];
        a[1] = sbox[a[1]];
        a[2] = sbox[a[2]];
        a[3] = sbox[a[3]];
    }

    void RotDWord(Bytes *a)
    {
        Bytes c = a[0];
        a[0] = a[1];
        a[1] = a[2];
        a[2] = a[3];
        a[3] = c;
    }

    void XorDWords(Bytes *a, Bytes *b, Bytes *dest)
    {
        dest[0] = a[0] ^ b[0];
        dest[1] = a[1] ^ b[1];
        dest[2] = a[2] ^ b[2];
        dest[3] = a[3] ^ b[3];
    }

    void XorBlocks(unsigned char *a, unsigned char * b, unsigned char *dest, unsigned int len)
    {
        for (unsigned int i = 0; i < len; i++)
        {
            dest[i] = a[i] ^ b[i];
        }
    }

    void Rcon(Bytes * a, int n)
    {
        int i;
        Bytes c = 1;
        for (i = 0; i < n - 1; i++)
        {
            c = xtime(c);
        }

        a[0] = c;
        a[1] = a[2] = a[3] = 0;
    }

    void printHexArray (unsigned char a[], size_t n)
    {
        for (size_t i = 0; i < n; i++) {
            printf("%02x ", a[i]);
        }
        std::cout << "\n";
    }

    void printHexVector (const std::vector<unsigned char>& a)
    {
        for (size_t i = 0; i < a.size(); i++) {
            printf("%02x ", a[i]);
        }
    }

    std::vector<unsigned char> ArrayToVector(unsigned char *a, unsigned char len)
    {
        std::vector<unsigned char> v(a, a + len * sizeof(unsigned char));
        return v;
    }

    unsigned char *VectorToArray(const std::vector<unsigned char>& a)
    {
        Bytes* cpy = new Bytes[a.size()];
        memcpy(cpy,a.data(),a.size());
        return cpy;
    }
}

#endif