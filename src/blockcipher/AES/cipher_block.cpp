#ifndef CIPHER_BLOCK_CPP
#define CIPHER_BLOCK_CPP

#include "AES.hpp"

namespace Krypt {
    namespace BlockCipher {
        void AES::EncryptBlock(Bytes *plain, Bytes *cipher) {
#ifdef USE_AESNI
            // load the current block & current round key into the registers
            __m128i state = _mm_loadu_si128((__m128i *) &plain[0]);

            // original key
            state = _mm_xor_si128(state, RoundedKeys[0]);

            // perform usual rounds
            for (size_t i = 1; i < Nr - 1; i += 2) {
                state = _mm_aesenc_si128(state, RoundedKeys[i]);
                state = _mm_aesenc_si128(state, RoundedKeys[i + 1]);
            }

            // last round
            state = _mm_aesenc_si128(state, RoundedKeys[Nr - 1]);
            state = _mm_aesenclast_si128(state, RoundedKeys[Nr]);

            // store from register to array
            _mm_storeu_si128((__m128i *) (cipher), state);
#elif defined(USE_ARM_AES)
            uint8x16_t state = vld1q_u8(plain);

            // Initial round
            state = vaesmcq_u8(vaeseq_u8(state, RoundedKeys[0]));

            // 8 main rounds
            for (size_t i = 1; i < Nr - 1; i += 2) {
                state = vaesmcq_u8(vaeseq_u8(state, RoundedKeys[i]));
                state = vaesmcq_u8(vaeseq_u8(state, RoundedKeys[i + 1]));
            }

            // last 2 final round
            state = vaeseq_u8(state, RoundedKeys[Nr - 1]);
            state = veorq_u8(state, RoundedKeys[Nr]);

            // store the result to cipher
            vst1q_u8(cipher, state);
#else
            Bytes state[16];

            state[0 * 4 + 0] = plain[0];
            state[0 * 4 + 1] = plain[4];
            state[0 * 4 + 2] = plain[8];
            state[0 * 4 + 3] = plain[12];

            state[1 * 4 + 0] = plain[1];
            state[1 * 4 + 1] = plain[5];
            state[1 * 4 + 2] = plain[9];
            state[1 * 4 + 3] = plain[13];

            state[2 * 4 + 0] = plain[2];
            state[2 * 4 + 1] = plain[6];
            state[2 * 4 + 2] = plain[10];
            state[2 * 4 + 3] = plain[14];

            state[3 * 4 + 0] = plain[3];
            state[3 * 4 + 1] = plain[7];
            state[3 * 4 + 2] = plain[11];
            state[3 * 4 + 3] = plain[15];

            AddRoundKey(state, RoundedKeys);

            for (uint8_t round = 1; round <= Nr - 1; round++) {
                SubBytes(state);
                ShiftRows(state);
                MixColumns(state);
                AddRoundKey(state, RoundedKeys + round * 4 * Nb);
            }

            SubBytes(state);
            ShiftRows(state);
            AddRoundKey(state, RoundedKeys + Nr * 4 * Nb);

            cipher[0] = state[0 * 4 + 0];
            cipher[4] = state[0 * 4 + 1];
            cipher[8] = state[0 * 4 + 2];
            cipher[12] = state[0 * 4 + 3];

            cipher[1] = state[1 * 4 + 0];
            cipher[5] = state[1 * 4 + 1];
            cipher[9] = state[1 * 4 + 2];
            cipher[13] = state[1 * 4 + 3];

            cipher[2] = state[2 * 4 + 0];
            cipher[6] = state[2 * 4 + 1];
            cipher[10] = state[2 * 4 + 2];
            cipher[14] = state[2 * 4 + 3];

            cipher[3] = state[3 * 4 + 0];
            cipher[7] = state[3 * 4 + 1];
            cipher[11] = state[3 * 4 + 2];
            cipher[15] = state[3 * 4 + 3];
#endif
        }

        void AES::DecryptBlock(Bytes *cipher, Bytes *recover) {
#ifdef USE_AESNI
            // load the current block & current round key into the registers
            __m128i state = _mm_loadu_si128((__m128i *) &cipher[0]);

            // first round
            state = _mm_xor_si128(state, DecryptionRoundedKeys[Nr]);

            // usual rounds
            for (size_t i = Nr - 1; i > 1; i -= 2) {
                state = _mm_aesdec_si128(state, DecryptionRoundedKeys[i]);
                state = _mm_aesdec_si128(state, DecryptionRoundedKeys[i - 1]);
            }

            // last round
            state = _mm_aesdec_si128(state, DecryptionRoundedKeys[1]);
            state = _mm_aesdeclast_si128(state, DecryptionRoundedKeys[0]);

            // store from register to array
            _mm_storeu_si128((__m128i *) recover, state);
#elif defined(USE_ARM_AES)
            uint8x16_t state = vld1q_u8(cipher);

            // Initial round
            state = vaesimcq_u8(vaesdq_u8(state, DecryptionRoundedKeys[Nr]));

            // 8 main rounds
            for (size_t i = Nr - 1; i > 1; i -= 2) {
                state = vaesimcq_u8(vaesdq_u8(state, DecryptionRoundedKeys[i]));
                state = vaesimcq_u8(vaesdq_u8(state, DecryptionRoundedKeys[i - 1]));
            }

            // final 2 rounds
            state = vaesdq_u8(state, DecryptionRoundedKeys[1]);
            state = veorq_u8(state, DecryptionRoundedKeys[0]);

            // store the result to recover
            vst1q_u8(recover, state);
#else
            Bytes state[16];

            state[0 * 4 + 0] = cipher[0];
            state[0 * 4 + 1] = cipher[4];
            state[0 * 4 + 2] = cipher[8];
            state[0 * 4 + 3] = cipher[12];
            state[1 * 4 + 0] = cipher[1];
            state[1 * 4 + 1] = cipher[5];
            state[1 * 4 + 2] = cipher[9];
            state[1 * 4 + 3] = cipher[13];
            state[2 * 4 + 0] = cipher[2];
            state[2 * 4 + 1] = cipher[6];
            state[2 * 4 + 2] = cipher[10];
            state[2 * 4 + 3] = cipher[14];
            state[3 * 4 + 0] = cipher[3];
            state[3 * 4 + 1] = cipher[7];
            state[3 * 4 + 2] = cipher[11];
            state[3 * 4 + 3] = cipher[15];

            AddRoundKey(state, RoundedKeys + Nr * 4 * Nb);

            for (uint8_t round = Nr - 1; round >= 1; round--) {
                InvSubBytes(state);
                InvShiftRows(state);
                AddRoundKey(state, RoundedKeys + round * 4 * Nb);
                InvMixColumns(state);
            }

            InvSubBytes(state);
            InvShiftRows(state);
            AddRoundKey(state, RoundedKeys);

            recover[0] = state[0 * 4 + 0];
            recover[4] = state[0 * 4 + 1];
            recover[8] = state[0 * 4 + 2];
            recover[12] = state[0 * 4 + 3];
            recover[1] = state[1 * 4 + 0];
            recover[5] = state[1 * 4 + 1];
            recover[9] = state[1 * 4 + 2];
            recover[13] = state[1 * 4 + 3];
            recover[2] = state[2 * 4 + 0];
            recover[6] = state[2 * 4 + 1];
            recover[10] = state[2 * 4 + 2];
            recover[14] = state[2 * 4 + 3];
            recover[3] = state[3 * 4 + 0];
            recover[7] = state[3 * 4 + 1];
            recover[11] = state[3 * 4 + 2];
            recover[15] = state[3 * 4 + 3];

#endif
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif