#ifndef AARCH_64_AES_HPP
#define AARCH_64_AES_HPP

#include <iostream>

#if defined(__aarch64__)

    #include <arm_neon.h>

// AES block encryption using 128-bit key
void neon_aes128_encrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesmcq_u8(vaeseq_u8(state, round_key[0]));

    // 8 main rounds
    for (int i = 1; i < 9; i++) {
        state = vaesmcq_u8(vaeseq_u8(state, round_key[i]));
    }

    // last 2 final round
    state = vaeseq_u8(state, round_key[9]);
    state = veorq_u8(state, round_key[10]);

    // store the result to output
    vst1q_u8(output, state);
}

// AES block decryption using 128-bit key
void neon_aes128_decrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesimcq_u8(vaesdq_u8(state, round_key[10]));

    // 8 main rounds
    for (int i = 9; i > 1; i--) {
        state = vaesimcq_u8(vaesdq_u8(state, round_key[i]));
    }

    // final 2 rounds
    state = vaesdq_u8(state, round_key[1]);
    state = veorq_u8(state, round_key[0]);

    // store the result to output
    vst1q_u8(output, state);
}

// aes 192

// AES block encryption using 192-bit key
void neon_aes192_encrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesmcq_u8(vaeseq_u8(state, round_key[0]));

    // 10 main rounds
    for (int i = 1; i < 11; i++) {
        state = vaesmcq_u8(vaeseq_u8(state, round_key[i]));
    }

    // last 2 final round
    state = vaeseq_u8(state, round_key[11]);
    state = veorq_u8(state, round_key[12]);

    // store the result to output
    vst1q_u8(output, state);
}

// AES block decryption using 192-bit key
void neon_aes192_decrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesimcq_u8(vaesdq_u8(state, round_key[12]));

    // 10 main rounds
    for (int i = 11; i > 1; i--) {
        state = vaesimcq_u8(vaesdq_u8(state, round_key[i]));
    }

    // final 2 rounds
    state = vaesdq_u8(state, round_key[1]);
    state = veorq_u8(state, round_key[0]);

    // store the result to output
    vst1q_u8(output, state);
}

// aes 256

// AES block encryption using 256-bit key
void neon_aes256_encrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesmcq_u8(vaeseq_u8(state, round_key[0]));

    // 12 main rounds
    for (int i = 1; i < 13; i++) {
        state = vaesmcq_u8(vaeseq_u8(state, round_key[i]));
    }

    // last 2 final round
    state = vaeseq_u8(state, round_key[13]);
    state = veorq_u8(state, round_key[14]);

    // store the result to output
    vst1q_u8(output, state);
}

// AES block decryption using 256-bit key
void neon_aes256_decrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesimcq_u8(vaesdq_u8(state, round_key[14]));

    // 12 main rounds
    for (int i = 13; i > 1; i--) {
        state = vaesimcq_u8(vaesdq_u8(state, round_key[i]));
    }

    // final 2 rounds
    state = vaesdq_u8(state, round_key[1]);
    state = veorq_u8(state, round_key[0]);

    // store the result to output
    vst1q_u8(output, state);
}

#endif

#endif