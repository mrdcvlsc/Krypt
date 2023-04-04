#ifndef AARCH_64_AES_HPP
#define AARCH_64_AES_HPP

#include <iostream>

// MACROS : https://github.com/noloader/AES-Intrinsics/blob/master/aes-arm.c
#if defined(__arm__) || defined(__aarch32__) || defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM)

    #if defined(__GNUC__)
        #include <stdint.h>
    #endif

    #if defined(__ARM_NEON) || defined(_MSC_VER)
        #include <arm_neon.h>
    #endif

    /* GCC and LLVM Clang, but not Apple Clang */
    #if defined(__GNUC__) && !defined(__apple_build_version__)
        #if defined(__ARM_ACLE) || defined(__ARM_FEATURE_CRYPTO)
            #include <arm_acle.h>
        #endif
    #endif

// AES block encryption using 128-bit key
void neon_aes_block_encrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key, size_t Nr) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesmcq_u8(vaeseq_u8(state, round_key[0]));

    // 8 main rounds
    for (size_t i = 1; i < Nr - 1; i += 2) {
        state = vaesmcq_u8(vaeseq_u8(state, round_key[i]));
        state = vaesmcq_u8(vaeseq_u8(state, round_key[i + 1]));
    }

    // last 2 final round
    state = vaeseq_u8(state, round_key[Nr - 1]);
    state = veorq_u8(state, round_key[Nr]);

    // store the result to output
    vst1q_u8(output, state);
}

// AES block decryption using 128-bit key
void neon_aes_block_decrypt(const uint8_t *input, uint8_t *output, const uint8x16_t *round_key, size_t Nr) {
    uint8x16_t state = vld1q_u8(input);

    // Initial round
    state = vaesimcq_u8(vaesdq_u8(state, round_key[Nr]));

    // 8 main rounds
    for (size_t i = Nr - 1; i > 1; i -= 2) {
        state = vaesimcq_u8(vaesdq_u8(state, round_key[i]));
        state = vaesimcq_u8(vaesdq_u8(state, round_key[i - 1]));
    }

    // final 2 rounds
    state = vaesdq_u8(state, round_key[1]);
    state = veorq_u8(state, round_key[0]);

    // store the result to output
    vst1q_u8(output, state);
}

#endif

#endif