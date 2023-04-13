#ifndef CBC_MODE_CPP
#define CBC_MODE_CPP

#include "../bytearray.hpp"
#include "../mode.hpp"

namespace Krypt {
    namespace Mode {
        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        CBC<CIPHER_TYPE, PADDING_TYPE>::CBC(const Bytes *key, size_t keyLen) : MODE() {
            Encryption = new CIPHER_TYPE(key, keyLen);
            PaddingScheme = new PADDING_TYPE();
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        ByteArray CBC<CIPHER_TYPE, PADDING_TYPE>::encrypt(Bytes *plain, size_t plainLen, Bytes *iv) {
            ByteArray padded = PaddingScheme->AddPadding(plain, plainLen, Encryption->BLOCK_SIZE);
            Bytes *tempIV = new Bytes[Encryption->BLOCK_SIZE];
            Bytes *cipher = new Bytes[padded.length];

            memcpy(tempIV, iv, Encryption->BLOCK_SIZE);

            for (size_t i = 0; i < padded.length; i += Encryption->BLOCK_SIZE) {
                this->blockEncrypt(padded.array + i, cipher + i, tempIV);
            }

            delete[] tempIV;
            return ByteArray(cipher, padded.length);
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        ByteArray CBC<CIPHER_TYPE, PADDING_TYPE>::decrypt(Bytes *cipher, size_t cipherLen, Bytes *iv) {
            Bytes *recover = new Bytes[cipherLen];
            Bytes *tempIV = new Bytes[Encryption->BLOCK_SIZE];
            memcpy(tempIV, iv, Encryption->BLOCK_SIZE);

            for (size_t i = 0; i < cipherLen; i += Encryption->BLOCK_SIZE) {
                this->blockDecrypt(cipher + i, recover + i, tempIV);
            }

            ByteArray recoverNoPadding = PaddingScheme->RemovePadding(recover, cipherLen, Encryption->BLOCK_SIZE);

            delete[] tempIV;
            delete[] recover;

            return recoverNoPadding;
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        void CBC<CIPHER_TYPE, PADDING_TYPE>::blockEncrypt(Bytes *plain, Bytes *cipher, Bytes *iv) {
            XorAesBlock(iv, plain, iv);
            Encryption->EncryptBlock(iv, cipher);
            memcpy(iv, cipher, 16);
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        void CBC<CIPHER_TYPE, PADDING_TYPE>::blockDecrypt(Bytes *cipher, Bytes *recover, Bytes *iv) {
            Encryption->DecryptBlock(cipher, recover);
            XorAesBlock(iv, recover, recover);
            memcpy(iv, cipher, Encryption->BLOCK_SIZE);
        }

    } // namespace Mode
} // namespace Krypt

#endif