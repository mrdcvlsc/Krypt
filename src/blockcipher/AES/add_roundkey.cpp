#ifndef ADD_ROUND_KEY_CPP
#define ADD_ROUND_KEY_CPP

#include "../../blockcipher.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::AddRoundKey(unsigned char state[4][4], unsigned char *key) {
            state[0][0] = state[0][0] ^ key[0];
            state[0][1] = state[0][1] ^ key[4];
            state[0][2] = state[0][2] ^ key[8];
            state[0][3] = state[0][3] ^ key[12];

            state[1][0] = state[1][0] ^ key[1];
            state[1][1] = state[1][1] ^ key[5];
            state[1][2] = state[1][2] ^ key[9];
            state[1][3] = state[1][3] ^ key[13];

            state[2][0] = state[2][0] ^ key[2];
            state[2][1] = state[2][1] ^ key[6];
            state[2][2] = state[2][2] ^ key[10];
            state[2][3] = state[2][3] ^ key[14];

            state[3][0] = state[3][0] ^ key[3];
            state[3][1] = state[3][1] ^ key[7];
            state[3][2] = state[3][2] ^ key[11];
            state[3][3] = state[3][3] ^ key[15];
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif