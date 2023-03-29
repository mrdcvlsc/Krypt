#ifndef KRYPT_MODE_OF_ENCRYPTION_HPP
#define KRYPT_MODE_OF_ENCRYPTION_HPP

#include "blockcipher.hpp"
#include "padding.hpp"
#include "types.hpp"
#include <iostream>

namespace Krypt {
    namespace Mode {
        class MODE {
            public:

            BlockCipher::BASE_BLOCKCIPHER *Encryption;
            Padding::NoPadding *PaddingScheme;

            MODE() {
                Encryption = NULL;
                PaddingScheme = NULL;
            }

            virtual ByteArray encrypt(Bytes *, size_t, Bytes *) = 0;
            virtual ByteArray decrypt(Bytes *, size_t, Bytes *) = 0;

            virtual void blockEncrypt(Bytes *, Bytes *, Bytes *) = 0;
            virtual void blockDecrypt(Bytes *, Bytes *, Bytes *) = 0;

            ~MODE() {
                delete Encryption;
                delete PaddingScheme;
            }
        };

        /// Electronic Code Blocking.
        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        class ECB : public MODE {
            public:

            ECB(const Bytes *key, size_t keyLen);
            /// encrypts the whole plain array using ECB mode of encryption with a chosen BlockCipher and Padding.
            /// @param plain pointer to a Bytes*/unsigned char* array, this is the array you want to encrypt.
            /// @param plainLen this is the size of the *plain array.
            /// @param iv for ECB passing an iv will not do anything so there is no need to provide this function an iv
            /// array.
            ByteArray encrypt(Bytes *plain, size_t plainLen, Bytes *iv = NULL) override;
            /// decrypts the whole cipher array using ECB mode of decryption with a chosen BlockCipher and Padding.
            /// @param cipher pointer to a Bytes*/unsigned char* array, this is the array you want to decrypt.
            /// @param cipherLen this is the size of the *cipher array.
            /// @param iv for ECB passing an iv will not do anything so there is no need to provide this function an iv
            /// array.
            ByteArray decrypt(Bytes *cipher, size_t cipherLen, Bytes *iv = NULL) override;

            void blockEncrypt(Bytes *plain, Bytes *cipher, Bytes *iv = NULL) override;
            void blockDecrypt(Bytes *plain, Bytes *cipher, Bytes *iv = NULL) override;
        };

        /// Cipher Block Chaining.
        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        class CBC : public MODE {
            public:

            CBC(const Bytes *key, size_t keyLen);
            /// encrypts the whole plain array using CBC mode of encryption with a chosen BlockCipher and Padding.
            /// @param plain pointer to a Bytes*/unsigned char* array, this is the array you want to encrypt.
            /// @param plainLen this is the size of the *plain array.
            /// @param iv the initial array use for the XOR'ing operations during the CBC encryption.
            ByteArray encrypt(Bytes *plain, size_t plainLen, Bytes *iv) override;
            /// decrypts the whole cipher array using CBC mode of decryption with a chosen BlockCipher and Padding.
            /// @param cipher pointer to a Bytes*/unsigned char* array, this is the array you want to decrypt.
            /// @param cipherLen this is the size of the *cipher array.
            /// @param iv the initial array use for the XOR'ing operations during the CBC decryption.
            ByteArray decrypt(Bytes *cipher, size_t cipherLen, Bytes *iv) override;

            void blockEncrypt(Bytes *plain, Bytes *cipher, Bytes *iv) override;
            void blockDecrypt(Bytes *plain, Bytes *cipher, Bytes *iv) override;
        };

        /// Cipher Feedback.
        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        class CFB : public MODE {
            public:

            CFB(const Bytes *key, size_t keyLen);
            /// encrypts the whole plain array using CFB mode of encryption with a chosen BlockCipher and Padding.
            /// @param plain pointer to a Bytes*/unsigned char* array, this is the array you want to encrypt.
            /// @param plainLen this is the size of the *plain array.
            /// @param iv the initial array use for the XOR'ing operations during the CFB encryption.
            ByteArray encrypt(Bytes *plain, size_t plainLen, Bytes *iv) override;
            /// decrypts the whole cipher array using CFB mode of decryption with a chosen BlockCipher and Padding.
            /// @param cipher pointer to a Bytes*/unsigned char* array, this is the array you want to decrypt.
            /// @param cipherLen this is the size of the *cipher array.
            /// @param iv the initial array use for the XOR'ing operations during the CFB decryption.
            ByteArray decrypt(Bytes *cipher, size_t cipherLen, Bytes *iv) override;

            void blockEncrypt(Bytes *plain, Bytes *cipher, Bytes *iv) override;
            void blockDecrypt(Bytes *plain, Bytes *cipher, Bytes *iv) override;
        };
    } // namespace Mode
} // namespace Krypt

#include "mode/cbc_mode.cpp"
#include "mode/cfb_mode.cpp"
#include "mode/ecb_mode.cpp"

#endif