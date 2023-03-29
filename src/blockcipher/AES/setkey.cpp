#ifndef KRYPT_AES_CPP
#define KRYPT_AES_CPP

#include "../../blockcipher.hpp"
#include <iostream>

namespace Krypt {
    namespace BlockCipher {
        void AES::setKey(const Bytes *ByteArray, size_t keyLen) {
            switch (keyLen) {
                case 16: // AES128
                    this->Nk = 4;
                    this->Nr = 10;
                    break;
                case 24: // AES192
                    this->Nk = 6;
                    this->Nr = 12;
                    break;
                case 32: // AES256
                    this->Nk = 8;
                    this->Nr = 14;
                    break;
                default:
                    throw std::invalid_argument("Incorrect key length");
            }

            KeyExpansion(ByteArray);
        }

        AES::AES(const Bytes *ByteArray, size_t keyLen) : BASE_BLOCKCIPHER(16) {
            setKey(ByteArray, keyLen);
        }

        AES::~AES() {
            if (RoundedKeys != NULL) {
                delete[] RoundedKeys;

#if defined(USE_AESNI) || defined(USE_ARM_AES)
                delete[] DecryptionRoundedKeys;
#endif
            }
        }
    } // namespace BlockCipher
} // namespace Krypt

#endif
