#ifndef KRYPT_BLOCKCIPHER_HPP
#define KRYPT_BLOCKCIPHER_HPP

#include <cstring>
#include <exception>
#include <iostream>

#ifdef USE_AESNI
    #include <bitset>
    #include <immintrin.h>
    #include <stdio.h>
#elif defined(USE_ARM_AES)
    #if defined(__aarch64__)
        #include <arm_neon.h>
    #endif
#endif

#include "functions.hpp"
#include "types.hpp"

namespace Krypt {
    namespace BlockCipher {
        class BASE_BLOCKCIPHER {
            public:

            size_t BLOCK_SIZE;

            BASE_BLOCKCIPHER(size_t blockSize) : BLOCK_SIZE(blockSize) {
            }

            /// encrypts a fixed 16 byte block from `src` into `dest`.
            /// @param src a pointer to an array of unsigned char*/Bytes* in heap this is
            /// the array you want to encrypt.
            /// @param dest another pointer to an array of unsigned char*/Bytes* in heap
            /// this is the array where the encrypted block will be stored.
            virtual void EncryptBlock(Bytes *, Bytes *) = 0;

            /// decrypts a fixed 16 byte block from `src` into `dest`.
            /// @param src a pointer to an array of unsigned char*/Bytes* in heap this is
            /// the array you want to decrypt.
            /// @param dest another pointer to an array of unsigned char*/Bytes* in heap
            /// this is the array where the decrypted block will be stored.
            virtual void DecryptBlock(Bytes *, Bytes *) = 0;

            virtual ~BASE_BLOCKCIPHER() = default;
        };

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

            inline void SubBytes(unsigned char state[4][4]);
            inline void InvSubBytes(unsigned char state[4][4]);

            inline void ShiftRows(unsigned char state[4][4]);
            inline void InvShiftRows(unsigned char state[4][4]);

            inline void MixColumns(unsigned char state[4][4]);
            inline void InvMixColumns(unsigned char state[4][4]);

            void AddRoundKey(unsigned char state[4][4], unsigned char *key);

            public:

            /// encrypts a fixed 16 byte block from `src` into `dest`.
            /// @param src a pointer to an array of unsigned char*/Bytes* in heap this is
            /// the array you want to encrypt.
            /// @param dest another pointer to an array of unsigned char*/Bytes* in heap
            /// this is the array where the encrypted block will be stored.
            void EncryptBlock(Bytes *src, Bytes *dest) override;

            /// decrypts a fixed 16 byte block from `src` into `dest`.
            /// @param src a pointer to an array of unsigned char*/Bytes* in heap this is
            /// the array you want to decrypt.
            /// @param dest another pointer to an array of unsigned char*/Bytes* in heap
            /// this is the array where the decrypted block will be stored.
            void DecryptBlock(Bytes *src, Bytes *dest) override;

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

#include "blockcipher/AES/add_roundkey.cpp"
#include "blockcipher/AES/cipher_block.cpp"
#include "blockcipher/AES/key_expansion.cpp"
#include "blockcipher/AES/mix_columns.cpp"
#include "blockcipher/AES/setkey.cpp"
#include "blockcipher/AES/shift_rows.cpp"
#include "blockcipher/AES/sub_bytes.cpp"

#endif
