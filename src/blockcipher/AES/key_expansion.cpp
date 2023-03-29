#ifndef KEY_EXPANSION_CPP
#define KEY_EXPANSION_CPP

#ifdef USE_AESNI
    #include <bitset>
    #include <immintrin.h>
    #include <stdio.h>
#endif

#include "../../blockcipher.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::KeyExpansion(const Bytes *key) {
            Bytes *w = new Bytes[4 * Nb * (Nr + 1)];
            Bytes *temp = new Bytes[4];
            Bytes *rcon = new Bytes[4];

            size_t i = 0;
            while (i < 4 * Nk) {
                w[i] = key[i];
                i++;
            }

            i = 4 * Nk;
            while (i < 4 * Nb * (Nr + 1)) {
                temp[0] = w[i - 4 + 0];
                temp[1] = w[i - 4 + 1];
                temp[2] = w[i - 4 + 2];
                temp[3] = w[i - 4 + 3];

                if (i / 4 % Nk == 0) {
                    RotDWord(temp);
                    SubDWordBytes(temp);
                    Rcon(rcon, i / (Nk * 4));
                    XorDWords(temp, rcon, temp);
                } else if (Nk > 6 && i / 4 % Nk == 4) {
                    SubDWordBytes(temp);
                }

                w[i + 0] = w[i - 4 * Nk] ^ temp[0];
                w[i + 1] = w[i + 1 - 4 * Nk] ^ temp[1];
                w[i + 2] = w[i + 2 - 4 * Nk] ^ temp[2];
                w[i + 3] = w[i + 3 - 4 * Nk] ^ temp[3];
                i += 4;
            }

            delete[] rcon;
            delete[] temp;

#ifdef USE_AESNI
            size_t RoundKeySize = Nr + 1;
            RoundedKeys = new __m128i[RoundKeySize];
            DecryptionRoundedKeys = new __m128i[RoundKeySize];

            RoundedKeys[0] = _mm_loadu_si128((__m128i *) &w[0]);
            DecryptionRoundedKeys[0] = RoundedKeys[0];

            for (size_t i = 1; i < RoundKeySize; ++i) {
                RoundedKeys[i] = _mm_loadu_si128((__m128i *) &w[i * 4 * Nb]);
                DecryptionRoundedKeys[i] = _mm_aesimc_si128(RoundedKeys[i]);
            }

            RoundedKeys[Nr] = _mm_loadu_si128((__m128i *) &w[Nr * 4 * Nb]);
            DecryptionRoundedKeys[Nr] = RoundedKeys[Nr];

            delete[] w;
#elif defined(USE_ARM_AES)
            size_t RoundKeySize = Nr + 1;
            RoundedKeys = new uint8x16_t[RoundKeySize];
            DecryptionRoundedKeys = new uint8x16_t[RoundKeySize];

            RoundedKeys[0] = vld1q_u8(&w[0]);
            DecryptionRoundedKeys[0] = vld1q_u8(&w[0]);

            for (size_t i = 1; i < RoundKeySize; ++i) {
                RoundedKeys[i] = vld1q_u8(&w[i * 4 * Nb]);
                DecryptionRoundedKeys[i] = vaesimcq_u8(RoundedKeys[i]);
            }

            RoundedKeys[Nr] = vld1q_u8(&w[Nr * 4 * Nb]);
            DecryptionRoundedKeys[Nr] = RoundedKeys[Nr];

            delete[] w;
#else
            RoundedKeys = w;
#endif
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif