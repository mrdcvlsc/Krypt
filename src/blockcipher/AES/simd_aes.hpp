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

#include <stdio.h>
#include <immintrin.h>
#include <bitset>

// ------------------------- REFERENCE START -------------------------

// https://www.intel.com/content/dam/doc/white-paper/advanced-encryption-standard-new-instructions-set-paper.pdf
// Before an application attempts to use the AES instructions, it should verify that the
// processor supports these instructions. This should be done by checking that
// CPUID.01H:ECX.AES[bit 25] = 1. The following (assembly) code demonstrates this
// check. 

// GCC

#define cpuid(func,ax,bx,cx,dx) \
    __asm__ __volatile__ ("cpuid":\
    "=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (func));

int Check_CPU_support_AES()
{
    unsigned int a,b,c,d;
    cpuid(1, a,b,c,d);
    return (c & 0x2000000);
}

// -------------------------  REFERENCE END  -------------------------

bool AESNI_IS_AVAILABLE()
{
    std::bitset<32> ecx(Check_CPU_support_AES());
    return ecx[25];
}

// compile with -maes flag for gcc

typedef unsigned char Byte;

//=============================== AES128==================================

void Aes128BlockEncrypt(Byte* plain, Byte* cipher, __m128i* roundKeys)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &plain[0]);

    // first round
    state = _mm_xor_si128(state, roundKeys[0]);

    // next rounds
    state = _mm_aesenc_si128(state, roundKeys[1]);
    state = _mm_aesenc_si128(state, roundKeys[2]);
    state = _mm_aesenc_si128(state, roundKeys[3]);
    state = _mm_aesenc_si128(state, roundKeys[4]);
    state = _mm_aesenc_si128(state, roundKeys[5]);
    state = _mm_aesenc_si128(state, roundKeys[6]);
    state = _mm_aesenc_si128(state, roundKeys[7]);
    state = _mm_aesenc_si128(state, roundKeys[8]);
    state = _mm_aesenc_si128(state, roundKeys[9]);

    // last round
    state = _mm_aesenclast_si128(state,  roundKeys[10]);

    // store from register to array
    _mm_storeu_si128((__m128i*)(cipher),state);
}

/** Note:
 * The aes instruction uses “Inverse Cipher” for decryption, meaning it does not use the original round keys for decryption.
 * Instead it uses the “Equivalent Inverse Cipher” for decryption where InverseMixColumns is applied on the original round keys.
 **/
void Aes128BlockDecrypt(Byte* cipher, Byte* recover, __m128i* decryptionRoundKeys)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &cipher[0]);

    // first round
    state = _mm_xor_si128(state, decryptionRoundKeys[10]);

    // next rounds
    state = _mm_aesdec_si128(state, decryptionRoundKeys[9]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[8]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[7]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[6]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[5]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[4]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[3]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[2]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[1]);

    // last round
    state = _mm_aesdeclast_si128(state, decryptionRoundKeys[0]);

    // store from register to array
    _mm_storeu_si128((__m128i*)recover, state);
}

// ===================================== AES192 =====================================

void Aes192BlockEncrypt(Byte* plain, Byte* cipher, __m128i* roundKeys)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &plain[0]);
    
    // first round
    state = _mm_xor_si128(state, roundKeys[0]);

    // next rounds
    state = _mm_aesenc_si128(state, roundKeys[1]);
    state = _mm_aesenc_si128(state, roundKeys[2]);
    state = _mm_aesenc_si128(state, roundKeys[3]);
    state = _mm_aesenc_si128(state, roundKeys[4]);
    state = _mm_aesenc_si128(state, roundKeys[5]);
    state = _mm_aesenc_si128(state, roundKeys[6]);
    state = _mm_aesenc_si128(state, roundKeys[7]);
    state = _mm_aesenc_si128(state, roundKeys[8]);
    state = _mm_aesenc_si128(state, roundKeys[9]);
    state = _mm_aesenc_si128(state, roundKeys[10]);
    state = _mm_aesenc_si128(state, roundKeys[11]);

    // last round
    state = _mm_aesenclast_si128(state,  roundKeys[12]);

    // store from register to array
    _mm_storeu_si128((__m128i*)(cipher),state);
}

void Aes192BlockDecrypt(Byte* cipher, Byte* recover, __m128i* decryptionRoundKeys)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &cipher[0]);
    
    // first round
    state = _mm_xor_si128(state, decryptionRoundKeys[12]);

    // next rounds
    state = _mm_aesdec_si128(state, decryptionRoundKeys[11]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[10]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[9]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[8]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[7]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[6]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[5]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[4]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[3]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[2]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[1]);

    // last round
    state = _mm_aesdeclast_si128(state, decryptionRoundKeys[0]);

    // store from register to array
    _mm_storeu_si128((__m128i*)recover, state);
}

// ==================================== AES256 ================================

void Aes256BlockEncrypt(Byte* plain, Byte* cipher, __m128i* roundKeys)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &plain[0]);
    
    // first round
    state = _mm_xor_si128(state, roundKeys[0]);

    // next rounds
    state = _mm_aesenc_si128(state, roundKeys[1]);
    state = _mm_aesenc_si128(state, roundKeys[2]);
    state = _mm_aesenc_si128(state, roundKeys[3]);
    state = _mm_aesenc_si128(state, roundKeys[4]);
    state = _mm_aesenc_si128(state, roundKeys[5]);
    state = _mm_aesenc_si128(state, roundKeys[6]);
    state = _mm_aesenc_si128(state, roundKeys[7]);
    state = _mm_aesenc_si128(state, roundKeys[8]);
    state = _mm_aesenc_si128(state, roundKeys[9]);
    state = _mm_aesenc_si128(state, roundKeys[10]);
    state = _mm_aesenc_si128(state, roundKeys[11]);
    state = _mm_aesenc_si128(state, roundKeys[12]);
    state = _mm_aesenc_si128(state, roundKeys[13]);

    // last round
    state = _mm_aesenclast_si128(state,  roundKeys[14]);

    // store from register to array
    _mm_storeu_si128((__m128i*)(cipher),state);
}

void Aes256BlockDecrypt(Byte* cipher, Byte* recover, __m128i* decryptionRoundKeys)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &cipher[0]);
    
    // first round
    state = _mm_xor_si128(state, decryptionRoundKeys[14]);

    // next rounds
    state = _mm_aesdec_si128(state, decryptionRoundKeys[13]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[12]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[11]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[10]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[9]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[8]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[7]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[6]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[5]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[4]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[3]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[2]);
    state = _mm_aesdec_si128(state, decryptionRoundKeys[1]);

    // last round
    state = _mm_aesdeclast_si128(state, decryptionRoundKeys[0]);

    // store from register to array
    _mm_storeu_si128((__m128i*)recover, state);
}

#endif