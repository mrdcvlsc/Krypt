#ifndef SUB_BYTES_CPP
#define SUB_BYTES_CPP

#include "../../blockcipher.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::SubBytes(unsigned char state[4][4]) {
            state[0][0] = sbox[state[0][0]];
            state[0][1] = sbox[state[0][1]];
            state[0][2] = sbox[state[0][2]];
            state[0][3] = sbox[state[0][3]];

            state[1][0] = sbox[state[1][0]];
            state[1][1] = sbox[state[1][1]];
            state[1][2] = sbox[state[1][2]];
            state[1][3] = sbox[state[1][3]];

            state[2][0] = sbox[state[2][0]];
            state[2][1] = sbox[state[2][1]];
            state[2][2] = sbox[state[2][2]];
            state[2][3] = sbox[state[2][3]];

            state[3][0] = sbox[state[3][0]];
            state[3][1] = sbox[state[3][1]];
            state[3][2] = sbox[state[3][2]];
            state[3][3] = sbox[state[3][3]];
        }

        void AES::InvSubBytes(unsigned char state[4][4]) {
            state[0][0] = inv_sbox[state[0][0]];
            state[0][1] = inv_sbox[state[0][1]];
            state[0][2] = inv_sbox[state[0][2]];
            state[0][3] = inv_sbox[state[0][3]];

            state[1][0] = inv_sbox[state[1][0]];
            state[1][1] = inv_sbox[state[1][1]];
            state[1][2] = inv_sbox[state[1][2]];
            state[1][3] = inv_sbox[state[1][3]];

            state[2][0] = inv_sbox[state[2][0]];
            state[2][1] = inv_sbox[state[2][1]];
            state[2][2] = inv_sbox[state[2][2]];
            state[2][3] = inv_sbox[state[2][3]];

            state[3][0] = inv_sbox[state[3][0]];
            state[3][1] = inv_sbox[state[3][1]];
            state[3][2] = inv_sbox[state[3][2]];
            state[3][3] = inv_sbox[state[3][3]];
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif