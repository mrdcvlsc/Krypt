#ifndef CFB_MODE_CPP
#define CFB_MODE_CPP

#include "../bytearray.hpp"
#include "../mode.hpp"

namespace Krypt {
    namespace Mode {
        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        CFB<CIPHER_TYPE, PADDING_TYPE>::CFB(const Bytes *key, size_t keyLen) : MODE() {
            Encryption = new CIPHER_TYPE(key, keyLen);
            PaddingScheme = new PADDING_TYPE();
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        ByteArray CFB<CIPHER_TYPE, PADDING_TYPE>::encrypt(Bytes *plain, size_t plainLen, Bytes *iv) {
            ByteArray padded = PaddingScheme->AddPadding(plain, plainLen, Encryption->BLOCK_SIZE);

            Bytes *tempIV = new Bytes[Encryption->BLOCK_SIZE];
            Bytes *encIV = new Bytes[Encryption->BLOCK_SIZE];
            Bytes *cipher = new Bytes[padded.length];

            memcpy(tempIV, iv, Encryption->BLOCK_SIZE);

            for (size_t i = 0; i < padded.length; i += Encryption->BLOCK_SIZE) {
                blockEncrypt(padded.array + i, cipher + i, tempIV);
            }

            delete[] tempIV;
            delete[] encIV;

            return ByteArray(cipher, padded.length);
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        ByteArray CFB<CIPHER_TYPE, PADDING_TYPE>::decrypt(Bytes *cipher, size_t cipherLen, Bytes *iv) {
            Bytes *recover = new Bytes[cipherLen];
            Bytes *tempIV = new Bytes[Encryption->BLOCK_SIZE];
            Bytes *encIV = new Bytes[Encryption->BLOCK_SIZE];

            memcpy(tempIV, iv, Encryption->BLOCK_SIZE);

            for (size_t i = 0; i < cipherLen; i += Encryption->BLOCK_SIZE) {
                Encryption->EncryptBlock(tempIV, encIV);
                XorAesBlock(cipher + i, encIV, recover + i);
                memcpy(tempIV, cipher + i, Encryption->BLOCK_SIZE);
            }

            ByteArray recoverNoPadding = PaddingScheme->RemovePadding(recover, cipherLen, Encryption->BLOCK_SIZE);

            delete[] recover;
            delete[] tempIV;
            delete[] encIV;

            return recoverNoPadding;
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        void CFB<CIPHER_TYPE, PADDING_TYPE>::blockEncrypt(Bytes *plain, Bytes *cipher, Bytes *iv) {
            Encryption->EncryptBlock(iv, cipher);
            XorAesBlock(plain, cipher, cipher);
            memcpy(iv, cipher, Encryption->BLOCK_SIZE);
        }

        template <typename CIPHER_TYPE, typename PADDING_TYPE>
        void CFB<CIPHER_TYPE, PADDING_TYPE>::blockDecrypt(Bytes *cipher, Bytes *recover, Bytes *iv) {
            Encryption->EncryptBlock(iv, recover);
            XorAesBlock(cipher, recover, recover);
            memcpy(iv, cipher, Encryption->BLOCK_SIZE);
        }
    } // namespace Mode
} // namespace Krypt

#endif