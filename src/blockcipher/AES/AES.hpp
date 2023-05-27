#ifndef KRYPT_AES_HPP
#define KRYPT_AES_HPP

#include <cstring>
#include <exception>
#include <iostream>

#include "../../blockcipher.hpp"

#ifdef USE_AESNI
    #include <immintrin.h>
    #include <stdio.h>
#elif defined(USE_ARM_AES)
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
    #endif
#endif

namespace Krypt {
    namespace BlockCipher {
        /// Advance Encryption Standard.
        ///
        /// provides method of encryption and decryption.
        /// @warning the method of this class only operates on a 16 byte array of unsigned char* or Bytes*
        /// if you pass an array of unsigned char* in the method with less than 16 elements in it that will cause an
        /// access overflow.
        class AES : public BASE_BLOCKCIPHER {
            private:

            const static size_t Nb = 4;
            size_t Nk;
            size_t Nr;
#ifdef USE_AESNI
            __m128i *RoundedKeys;
            __m128i *DecryptionRoundedKeys;
#elif defined(USE_ARM_AES)
            uint8x16_t *RoundedKeys;
            uint8x16_t *DecryptionRoundedKeys;
#else
            Bytes *RoundedKeys;
#endif

            void KeyExpansion(const Bytes *key);

            inline void SubBytes(unsigned char state[16]);
            inline void InvSubBytes(unsigned char state[16]);

            inline void ShiftRows(unsigned char state[16]);
            inline void InvShiftRows(unsigned char state[16]);

            inline void MixColumns(unsigned char state[16]);
            inline void InvMixColumns(unsigned char state[16]);

            void AddRoundKey(unsigned char state[16], unsigned char *key);

            public:

            /// encrypts a fixed 16 byte block from `plain` into `cipher`.
            /// @param plain a pointer to an array of unsigned char*/Bytes* in heap this is
            /// the array you want to encrypt.
            /// @param cipher another pointer to an array of unsigned char*/Bytes* in heap
            /// this is the array where the encrypted block will be stored.
            void EncryptBlock(Bytes *plain, Bytes *cipher) override;

            /// decrypts a fixed 16 byte block from `cipher` into `recover`.
            /// @param cipher a pointer to an array of unsigned char*/Bytes* in heap this is
            /// the array you want to decrypt.
            /// @param recover another pointer to an array of unsigned char*/Bytes* in heap
            /// this is the array where the decrypted block will be stored.
            void DecryptBlock(Bytes *cipher, Bytes *recover) override;

            /// initialize the round key from a key.
            ///
            /// @note this function is automatically called when you initialize and object of AES,
            /// the only time you want to use or call this member method is when you want to change the
            /// key and the roundKeys of an instance of an AES class.
            void setKey(const Bytes *key, size_t keyLen);

            /// @return 0 - portable, 1 - neon (aarch64, armv8), 2 - AES-NI (x86-64)
            static constexpr int aes_implementation() {
                #ifdef USE_AESNI
                    return 2;
                #elif defined(USE_ARM_AES)
                    return 1;
                #else
                    return 0;
                #endif
            }

            /// constructor for AES.
            AES(const Bytes *ByteArray, size_t keyLen);
            ~AES();
        };
    } // namespace BlockCipher
} // namespace Krypt

#include "add_roundkey.cpp"
#include "cipher_block.cpp"
#include "key_expansion.cpp"
#include "mix_columns.cpp"
#include "setkey.cpp"
#include "shift_rows.cpp"
#include "sub_bytes.cpp"

#endif