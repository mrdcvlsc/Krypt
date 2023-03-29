#ifndef MIX_COLUMNS_CPP
#define MIX_COLUMNS_CPP

#include "../../blockcipher.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::MixColumns(unsigned char state[4][4]) {
            unsigned char temp_state[4][4];

            memset(temp_state, 0x00, 4 * 4);

            for (size_t i = 0; i < 4; ++i) {
                for (size_t k = 0; k < 4; ++k) {
                    for (size_t j = 0; j < 4; ++j) {
                        if (CMDS[i][k] == 1) {
                            temp_state[i][j] ^= state[k][j];
                        } else {
                            temp_state[i][j] ^= GF_MUL_TABLE[CMDS[i][k]][state[k][j]];
                        }
                    }
                }
            }

            memcpy(state, temp_state, 4 * 4);
        }

        void AES::InvMixColumns(unsigned char state[4][4]) {
            unsigned char temp_state[4][4];

            memset(temp_state, 0x00, 4 * 4);

            for (size_t i = 0; i < 4; ++i) {
                for (size_t k = 0; k < 4; ++k) {
                    for (size_t j = 0; j < 4; ++j) {
                        temp_state[i][j] ^= GF_MUL_TABLE[INV_CMDS[i][k]][state[k][j]];
                    }
                }
            }

            memcpy(state, temp_state, 4 * 4);
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif