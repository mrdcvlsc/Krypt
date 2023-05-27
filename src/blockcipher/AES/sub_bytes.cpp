#ifndef SUB_BYTES_CPP
#define SUB_BYTES_CPP

#include "AES.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::SubBytes(unsigned char state[16]) {
            state[0 * 4 + 0] = sbox[state[0 * 4 + 0]];
            state[0 * 4 + 1] = sbox[state[0 * 4 + 1]];
            state[0 * 4 + 2] = sbox[state[0 * 4 + 2]];
            state[0 * 4 + 3] = sbox[state[0 * 4 + 3]];

            state[1 * 4 + 0] = sbox[state[1 * 4 + 0]];
            state[1 * 4 + 1] = sbox[state[1 * 4 + 1]];
            state[1 * 4 + 2] = sbox[state[1 * 4 + 2]];
            state[1 * 4 + 3] = sbox[state[1 * 4 + 3]];

            state[2 * 4 + 0] = sbox[state[2 * 4 + 0]];
            state[2 * 4 + 1] = sbox[state[2 * 4 + 1]];
            state[2 * 4 + 2] = sbox[state[2 * 4 + 2]];
            state[2 * 4 + 3] = sbox[state[2 * 4 + 3]];

            state[3 * 4 + 0] = sbox[state[3 * 4 + 0]];
            state[3 * 4 + 1] = sbox[state[3 * 4 + 1]];
            state[3 * 4 + 2] = sbox[state[3 * 4 + 2]];
            state[3 * 4 + 3] = sbox[state[3 * 4 + 3]];
        }

        void AES::InvSubBytes(unsigned char state[16]) {
            state[0 * 4 + 0] = inv_sbox[state[0 * 4 + 0]];
            state[0 * 4 + 1] = inv_sbox[state[0 * 4 + 1]];
            state[0 * 4 + 2] = inv_sbox[state[0 * 4 + 2]];
            state[0 * 4 + 3] = inv_sbox[state[0 * 4 + 3]];

            state[1 * 4 + 0] = inv_sbox[state[1 * 4 + 0]];
            state[1 * 4 + 1] = inv_sbox[state[1 * 4 + 1]];
            state[1 * 4 + 2] = inv_sbox[state[1 * 4 + 2]];
            state[1 * 4 + 3] = inv_sbox[state[1 * 4 + 3]];

            state[2 * 4 + 0] = inv_sbox[state[2 * 4 + 0]];
            state[2 * 4 + 1] = inv_sbox[state[2 * 4 + 1]];
            state[2 * 4 + 2] = inv_sbox[state[2 * 4 + 2]];
            state[2 * 4 + 3] = inv_sbox[state[2 * 4 + 3]];

            state[3 * 4 + 0] = inv_sbox[state[3 * 4 + 0]];
            state[3 * 4 + 1] = inv_sbox[state[3 * 4 + 1]];
            state[3 * 4 + 2] = inv_sbox[state[3 * 4 + 2]];
            state[3 * 4 + 3] = inv_sbox[state[3 * 4 + 3]];
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif