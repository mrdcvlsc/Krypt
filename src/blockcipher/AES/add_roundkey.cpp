#ifndef ADD_ROUND_KEY_CPP
#define ADD_ROUND_KEY_CPP

#include "AES.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::AddRoundKey(unsigned char state[16], unsigned char *key) {
            state[0 * 4 + 0] = state[0 * 4 + 0] ^ key[0];
            state[0 * 4 + 1] = state[0 * 4 + 1] ^ key[4];
            state[0 * 4 + 2] = state[0 * 4 + 2] ^ key[8];
            state[0 * 4 + 3] = state[0 * 4 + 3] ^ key[12];

            state[1 * 4 + 0] = state[1 * 4 + 0] ^ key[1];
            state[1 * 4 + 1] = state[1 * 4 + 1] ^ key[5];
            state[1 * 4 + 2] = state[1 * 4 + 2] ^ key[9];
            state[1 * 4 + 3] = state[1 * 4 + 3] ^ key[13];

            state[2 * 4 + 0] = state[2 * 4 + 0] ^ key[2];
            state[2 * 4 + 1] = state[2 * 4 + 1] ^ key[6];
            state[2 * 4 + 2] = state[2 * 4 + 2] ^ key[10];
            state[2 * 4 + 3] = state[2 * 4 + 3] ^ key[14];

            state[3 * 4 + 0] = state[3 * 4 + 0] ^ key[3];
            state[3 * 4 + 1] = state[3 * 4 + 1] ^ key[7];
            state[3 * 4 + 2] = state[3 * 4 + 2] ^ key[11];
            state[3 * 4 + 3] = state[3 * 4 + 3] ^ key[15];
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif