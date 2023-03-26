#ifndef CIPHER_BLOCK_CPP
#define CIPHER_BLOCK_CPP

#include "../../blockcipher.hpp"

#ifdef USE_AESNI
#include "simd_aes.hpp"
#endif

namespace Krypt
{
    namespace BlockCipher
    {
        void AES::EncryptBlock(Bytes *src, Bytes *dest)
        {
            #ifdef USE_AESNI
            switch (Nr)
            {
            case 10: Aes128BlockEncrypt(src, dest, RoundedKeys); break;
            case 12: Aes192BlockEncrypt(src, dest, RoundedKeys); break;
            case 14: Aes256BlockEncrypt(src, dest, RoundedKeys); break;
            default: throw std::invalid_argument("Incorrect key length");
            }
            #else

            Bytes state[4][4];

            state[0][0] = src[0];
            state[0][1] = src[4];
            state[0][2] = src[8];
            state[0][3] = src[12];

            state[1][0] = src[1];
            state[1][1] = src[5];
            state[1][2] = src[9];
            state[1][3] = src[13];

            state[2][0] = src[2];
            state[2][1] = src[6];
            state[2][2] = src[10];
            state[2][3] = src[14];

            state[3][0] = src[3];
            state[3][1] = src[7];
            state[3][2] = src[11];
            state[3][3] = src[15];

            AddRoundKey(state, RoundedKeys);

            for (uint8_t round = 1; round <= Nr - 1; round++)
            {
                SubBytes(state);
                ShiftRows(state);
                MixColumns(state);
                AddRoundKey(state, RoundedKeys + round * 4 * Nb);
            }

            SubBytes(state);
            ShiftRows(state);
            AddRoundKey(state, RoundedKeys + Nr * 4 * Nb);

            dest[0] = state[0][0];
            dest[4] = state[0][1];
            dest[8] = state[0][2];
            dest[12] = state[0][3];

            dest[1] = state[1][0];
            dest[5] = state[1][1];
            dest[9] = state[1][2];
            dest[13] = state[1][3];

            dest[2] = state[2][0];
            dest[6] = state[2][1];
            dest[10] = state[2][2];
            dest[14] = state[2][3];

            dest[3] = state[3][0];
            dest[7] = state[3][1];
            dest[11] = state[3][2];
            dest[15] = state[3][3];

            #endif
        }

        void AES::DecryptBlock(Bytes *src, Bytes *dest)
        {
            #ifdef USE_AESNI
            switch (Nr)
            {
            case 10: Aes128BlockDecrypt(src, dest, DecryptionRoundedKeys); break;
            case 12: Aes192BlockDecrypt(src, dest, DecryptionRoundedKeys); break;
            case 14: Aes256BlockDecrypt(src, dest, DecryptionRoundedKeys); break;
            default: throw std::invalid_argument("Incorrect key length");
            }
            #else

            Bytes state[4][4];

            state[0][0] = src[0];
            state[0][1] = src[4];
            state[0][2] = src[8];
            state[0][3] = src[12];
            state[1][0] = src[1];
            state[1][1] = src[5];
            state[1][2] = src[9];
            state[1][3] = src[13];
            state[2][0] = src[2];
            state[2][1] = src[6];
            state[2][2] = src[10];
            state[2][3] = src[14];
            state[3][0] = src[3];
            state[3][1] = src[7];
            state[3][2] = src[11];
            state[3][3] = src[15];

            AddRoundKey(state, RoundedKeys + Nr * 4 * Nb);

            for (uint8_t round = Nr - 1; round >= 1; round--)
            {
                InvSubBytes(state);
                InvShiftRows(state);
                AddRoundKey(state, RoundedKeys + round * 4 * Nb);
                InvMixColumns(state);
            }

            InvSubBytes(state);
            InvShiftRows(state);
            AddRoundKey(state, RoundedKeys);

            dest[0] = state[0][0];
            dest[4] = state[0][1];
            dest[8] = state[0][2];
            dest[12] = state[0][3];
            dest[1] = state[1][0];
            dest[5] = state[1][1];
            dest[9] = state[1][2];
            dest[13] = state[1][3];
            dest[2] = state[2][0];
            dest[6] = state[2][1];
            dest[10] = state[2][2];
            dest[14] = state[2][3];
            dest[3] = state[3][0];
            dest[7] = state[3][1];
            dest[11] = state[3][2];
            dest[15] = state[3][3];

            #endif
        }
    }
}

#endif