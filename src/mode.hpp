#ifndef KRYPT_MODE_OF_ENCRYPTION_HPP
#define KRYPT_MODE_OF_ENCRYPTION_HPP

#include <iostream>
#include "types.hpp"
#include "blockcipher.hpp"
#include "padding.hpp"

namespace Krypt::Mode
{
    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    class MODE
    {
        public:
            BlockCipher::BASE_BLOCKCIPHER* Encryption;
            Padding::NoPadding* PaddingScheme;

            MODE()
            {
                Encryption = NULL;
                PaddingScheme = NULL;
            }

            virtual ByteArray encrypt(Bytes*, size_t, Bytes*) { return {NULL,0}; }
            virtual ByteArray decrypt(Bytes*, size_t, Bytes*) { return {NULL,0}; }

            ~MODE()
            {
                delete Encryption;
                delete PaddingScheme;
            }
    };

    /// Electronic Code Blocking.
    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    class ECB : public MODE<CIPHER_TYPE,PADDING_TYPE>
    {
        public:
            ECB(const Bytes* key, size_t keyLen);
            /// encrypts the whole plain array using ECB mode of encryption with a chosen BlockCipher and Padding.
            /// @param plain pointer to a Bytes*/unsigned char* array, this is the array you want to encrypt.
            /// @param plainLen this is the size of the *plain array.
            /// @param iv for ECB passing an iv will not do anything so there is no need to provide this function an iv array.
            ByteArray encrypt(Bytes* plain, size_t plainLen, Bytes* iv=NULL) override;
            /// decrypts the whole cipher array using ECB mode of decryption with a chosen BlockCipher and Padding.
            /// @param cipher pointer to a Bytes*/unsigned char* array, this is the array you want to decrypt.
            /// @param cipherLen this is the size of the *cipher array.
            /// @param iv for ECB passing an iv will not do anything so there is no need to provide this function an iv array.
            ByteArray decrypt(Bytes* cipher, size_t cipherLen, Bytes* iv=NULL) override;
    };

    /// Cipher Block Chaining.
    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    class CBC : public MODE<CIPHER_TYPE,PADDING_TYPE>
    {
        public:
            CBC(const Bytes* key, size_t keyLen);
            /// encrypts the whole plain array using CBC mode of encryption with a chosen BlockCipher and Padding.
            /// @param plain pointer to a Bytes*/unsigned char* array, this is the array you want to encrypt.
            /// @param plainLen this is the size of the *plain array.
            /// @param iv the initial array use for the XOR'ing operations during the CBC encryption.
            ByteArray encrypt(Bytes* plain, size_t plainLen, Bytes* iv) override;
            /// decrypts the whole cipher array using CBC mode of decryption with a chosen BlockCipher and Padding.
            /// @param cipher pointer to a Bytes*/unsigned char* array, this is the array you want to decrypt.
            /// @param cipherLen this is the size of the *cipher array.
            /// @param iv the initial array use for the XOR'ing operations during the CBC decryption.
            ByteArray decrypt(Bytes* cipher, size_t cipherLen, Bytes* iv) override;
    };

    /// Cipher Feedback.
    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    class CFB : public MODE<CIPHER_TYPE,PADDING_TYPE>
    {
        public:
            CFB(const Bytes* key, size_t keyLen);
            /// encrypts the whole plain array using CFB mode of encryption with a chosen BlockCipher and Padding.
            /// @param plain pointer to a Bytes*/unsigned char* array, this is the array you want to encrypt.
            /// @param plainLen this is the size of the *plain array.
            /// @param iv the initial array use for the XOR'ing operations during the CFB encryption.
            ByteArray encrypt(Bytes* plain, size_t plainLen, Bytes* iv) override;
            /// decrypts the whole cipher array using CFB mode of decryption with a chosen BlockCipher and Padding.
            /// @param cipher pointer to a Bytes*/unsigned char* array, this is the array you want to decrypt.
            /// @param cipherLen this is the size of the *cipher array.
            /// @param iv the initial array use for the XOR'ing operations during the CFB decryption.
            ByteArray decrypt(Bytes* cipher, size_t cipherLen, Bytes* iv) override;
    };
}

#include "mode/cbc_mode.cpp"
#include "mode/cfb_mode.cpp"
#include "mode/ecb_mode.cpp"

#endif