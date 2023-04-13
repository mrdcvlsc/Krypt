#ifndef AES_BLOCK_ENCRYPTION_USING_SIMD_AES_INSTRUCTION
#define AES_BLOCK_ENCRYPTION_USING_SIMD_AES_INSTRUCTION

// Dec-23-2021

/* ====================== CONTENTS ======================

Byte == unsigned char

bool AESNI_IS_AVAILABLE();
void AesBlockEncrypt(Byte* plain, Byte* cipher, __m128i* roundKeys)
void AesBlockDecrypt(Byte* cipher, Byte* recover, __m128i* roundKeys)

   ======================================================
*/

#include <bitset>
#include <immintrin.h>
#include <stdio.h>

// ------------------------- REFERENCE START -------------------------

// https://www.intel.com/content/dam/doc/white-paper/advanced-encryption-standard-new-instructions-set-paper.pdf
// Before an application attempts to use the AES instructions, it should verify that the
// processor supports these instructions. This should be done by checking that
// CPUID.01H:ECX.AES[bit 25] = 1. The following (assembly) code demonstrates this
// check.

// GCC

#define cpuid(func, ax, bx, cx, dx) __asm__ __volatile__("cpuid" : "=a"(ax), "=b"(bx), "=c"(cx), "=d"(dx) : "a"(func));

int Check_CPU_support_AES() {
    unsigned int a, b, c, d;
    cpuid(1, a, b, c, d);
    return (c & 0x2000000);
}

// -------------------------  REFERENCE END  -------------------------

bool AESNI_IS_AVAILABLE() {
    std::bitset<32> ecx(Check_CPU_support_AES());
    return ecx[25];
}

// compile with -maes flag for gcc

typedef unsigned char Byte;

//=============================== aes_b====_e============================

void aesni_block_encrypt(Byte *plain, Byte *cipher, __m128i *roundKeys, size_t Nr) {
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i *) &plain[0]);

    // original key
    state = _mm_xor_si128(state, roundKeys[0]);

    // perform usual rounds
    for (size_t i = 1; i < Nr - 1; i += 2) {
        state = _mm_aesenc_si128(state, roundKeys[i]);
        state = _mm_aesenc_si128(state, roundKeys[i + 1]);
    }

    // last round
    state = _mm_aesenc_si128(state, roundKeys[Nr - 1]);
    state = _mm_aesenclast_si128(state, roundKeys[Nr]);

    // store from register to array
    _mm_storeu_si128((__m128i *) (cipher), state);
}

/** Note:
 * The aes instruction uses “Inverse Cipher” for decryption, meaning it does not use the original round keys for
 *decryption. Instead it uses the “Equivalent Inverse Cipher” for decryption where InverseMixColumns is applied on the
 *original round keys.
 **/
void aesni_block_decrypt(Byte *cipher, Byte *recover, __m128i *decryptionRoundKeys, size_t Nr) {
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i *) &cipher[0]);

    // first round
    state = _mm_xor_si128(state, decryptionRoundKeys[Nr]);

    // usual rounds
    for (size_t i = Nr - 1; i > 1; i -= 2) {
        state = _mm_aesdec_si128(state, decryptionRoundKeys[i]);
        state = _mm_aesdec_si128(state, decryptionRoundKeys[i - 1]);
    }

    // last round
    state = _mm_aesdec_si128(state, decryptionRoundKeys[1]);
    state = _mm_aesdeclast_si128(state, decryptionRoundKeys[0]);

    // store from register to array
    _mm_storeu_si128((__m128i *) recover, state);
}

#endif