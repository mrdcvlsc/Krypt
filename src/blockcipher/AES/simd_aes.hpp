#ifndef AES_BLOCK_ENCRYPTION_USING_SIMD_AES_INSTRUCTION
#define AES_BLOCK_ENCRYPTION_USING_SIMD_AES_INSTRUCTION

// Dec-23-2021

/* ====================== CONTENTS ======================

Byte == unsigned char

bool AESNI_IS_AVAILABLE();
void AesBlockEncrypt(Byte* plain, Byte* cipher, Byte* roundKeys, int Nr, int)
void AesBlockDecrypt(Byte* cipher, Byte* recover, Byte* roundKeys, int Nr, int)

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

void Aes128BlockEncrypt(Byte* plain, Byte* cipher, Byte* roundKeys, int Nr, int)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &plain[0]);
    __m128i crkey = _mm_loadu_si128((__m128i*) &roundKeys[0]);

    // first round
    state = _mm_xor_si128(state, crkey);

    // next rounds
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[16]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[32]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[48]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[64]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[80]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[96]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[112]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[128]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[144]);  // round
    state = _mm_aesenc_si128(state,crkey);

    // last round
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[Nr*16]);
    state = _mm_aesenclast_si128(state, crkey);

    // store from register to array
    _mm_storeu_si128((__m128i*)(cipher),state);
}

/** Note:
 * The aes instruction uses “Inverse Cipher” for decryption, meaning it does not use the original round keys for decryption.
 * Instead it uses the “Equivalent Inverse Cipher” for decryption where InverseMixColumns is applied on the original round keys.
 **/
void Aes128BlockDecrypt(Byte* cipher, Byte* recover, Byte* roundKeys, int Nr, int)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &cipher[0]);
    __m128i crkey = _mm_loadu_si128((__m128i*) &roundKeys[Nr*16]);

    // first round
    state = _mm_xor_si128(state, crkey);

    // next rounds
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[144]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[128]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[112]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[96]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[80]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[64]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[48]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[32]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[16]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);

    // last round
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[0]);
    state = _mm_aesdeclast_si128(state, crkey);

    // store from register to array
    _mm_storeu_si128((__m128i*)recover, state);
}

// you can even optimized these two functions further by unrolling the "next rounds" for loop

// ===================================== AES192 =====================================

void Aes192BlockEncrypt(Byte* plain, Byte* cipher, Byte* roundKeys, int Nr, int)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &plain[0]);
    __m128i crkey = _mm_loadu_si128((__m128i*) &roundKeys[0]);

    // first round
    state = _mm_xor_si128(state, crkey);

    // next rounds
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[16]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[32]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[48]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[64]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[80]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[96]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[112]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[128]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[144]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[160]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[176]);  // round
    state = _mm_aesenc_si128(state,crkey);

    // last round
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[Nr*16]);
    state = _mm_aesenclast_si128(state, crkey);

    // store from register to array
    _mm_storeu_si128((__m128i*)(cipher), state);
}

void Aes192BlockDecrypt(Byte* cipher, Byte* recover, Byte* roundKeys, int Nr, int)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &cipher[0]);
    __m128i crkey = _mm_loadu_si128((__m128i*) &roundKeys[Nr*16]);

    // first round
    state = _mm_xor_si128(state, crkey);

    // next rounds
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[176]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[160]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[144]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[128]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[112]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[96]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[80]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[64]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[48]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[32]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[16]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);

    // last round
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[0]);
    state = _mm_aesdeclast_si128(state, crkey);

    // store from register to array
    _mm_storeu_si128((__m128i*)recover, state);
}

// ==================================== AES256 ================================

void Aes256BlockEncrypt(Byte* plain, Byte* cipher, Byte* roundKeys, int Nr, int)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &plain[0]);
    __m128i crkey = _mm_loadu_si128((__m128i*) &roundKeys[0]);

    // first round
    state = _mm_xor_si128(state, crkey);

    // next rounds
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[16]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[32]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[48]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[64]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[80]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[96]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[112]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[128]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[144]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[160]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[176]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[192]);  // round
    state = _mm_aesenc_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[208]);  // round
    state = _mm_aesenc_si128(state,crkey);

    // last round
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[Nr*16]);
    state = _mm_aesenclast_si128(state, crkey);

    // store from register to array
    _mm_storeu_si128((__m128i*)(cipher), state);
}

void Aes256BlockDecrypt(Byte* cipher, Byte* recover, Byte* roundKeys, int Nr, int)
{
    // load the current block & current round key into the registers
    __m128i state = _mm_loadu_si128((__m128i*) &cipher[0]);
    __m128i crkey = _mm_loadu_si128((__m128i*) &roundKeys[Nr*16]);

    // first round
    state = _mm_xor_si128(state, crkey);

    // next rounds
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[208]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[192]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[176]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[160]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[144]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[128]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[112]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[96]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[80]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[64]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[48]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[32]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[16]); // round
    crkey = _mm_aesimc_si128(crkey);
    state = _mm_aesdec_si128(state,crkey);

    // last round
    crkey = _mm_loadu_si128((__m128i*) &roundKeys[0]);
    state = _mm_aesdeclast_si128(state, crkey);

    // store from register to array
    _mm_storeu_si128((__m128i*)recover, state);
}

#endif