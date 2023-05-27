#ifndef KRYPT_BLOCKCIPHER_HPP
#define KRYPT_BLOCKCIPHER_HPP

#include <cstring>
#include <exception>
#include <iostream>

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
    } // namespace BlockCipher
} // namespace Krypt

#include "blockcipher/AES/AES.hpp"

#endif
