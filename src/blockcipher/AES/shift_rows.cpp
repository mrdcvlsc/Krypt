#ifndef SHIFT_ROWS_CPP
#define SHIFT_ROWS_CPP

#include "AES.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::ShiftRows(unsigned char state[16]) {
            // row 2
            unsigned char buffer = state[1 * 4 + 0];
            memmove(&state[4], &state[4] + 1, sizeof(unsigned char) * 3);
            state[1 * 4 + 3] = buffer;

            // row 3
            unsigned char thrid[2];
            memcpy(thrid, &state[8], sizeof(unsigned char) * 2);
            memcpy(&state[8], &state[8] + 2, sizeof(unsigned char) * 2);
            memcpy(&state[8] + 2, thrid, sizeof(unsigned char) * 2);

            // row 4
            buffer = state[3 * 4 + 3];
            memmove(&state[12] + 1, &state[12], sizeof(unsigned char) * 3);
            state[3 * 4 + 0] = buffer;

            /*
            unsigned char temp;

            //Row 2
            temp = state[1 * 4 + 0];
            state[1 * 4 + 0] = state[1 * 4 + 1];
            state[1 * 4 + 1] = state[1 * 4 + 2];
            state[1 * 4 + 2] = state[1 * 4 + 3];
            state[1 * 4 + 3] = temp;

            //Row 3
            temp = state[2 * 4 + 0];
            state[ * 4 + [0] = state[2 * 4 + 2];
            state[2 * 4 + 2] = temp;
            temp = state[2 * 4 + 1];
            state[2 * 4 + 1] = state[2 * 4 + 3];
            state[2 * 4 + 3] = temp;

            //Row 4
            temp = state[3 * 4 + 0];
            state[3 * 4 + 0] = state[3 * 4 + 3];
            state[3 * 4 + 3] = state[3 * 4 + 2];
            state[3 * 4 + 2] = state[3 * 4 + 1];
            state[3 * 4 + 1] = temp;
            */
        }

        void AES::InvShiftRows(unsigned char state[16]) {
            // row 2
            unsigned char buffer = state[1 * 4 + 3];
            memmove(&state[4] + 1, &state[4], sizeof(unsigned char) * 3);
            state[1 * 4 + 0] = buffer;

            // row 3
            unsigned char thrid[2];
            memcpy(thrid, &state[8], sizeof(unsigned char) * 2);
            memcpy(&state[8], &state[8] + 2, sizeof(unsigned char) * 2);
            memcpy(&state[8] + 2, thrid, sizeof(unsigned char) * 2);

            // row 4
            buffer = state[3 * 4 + 0];
            memmove(&state[12], &state[12] + 1, sizeof(unsigned char) * 3);
            state[3 * 4 + 3] = buffer;
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif