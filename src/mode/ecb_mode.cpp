#ifndef ECP_MODE_CPP
#define ECP_MODE_CPP

#include "../bytearray.hpp"
#include "../mode.hpp"

namespace Krypt
{
    namespace Mode
    {
        template<typename CIPHER_TYPE, typename PADDING_TYPE>
        ECB<CIPHER_TYPE,PADDING_TYPE>::ECB(const Bytes* key, size_t keyLen)
            : MODE()
        {
            this->Encryption = new CIPHER_TYPE(key,keyLen);
            this->PaddingScheme = new PADDING_TYPE();
        }

        template<typename CIPHER_TYPE, typename PADDING_TYPE>
        ByteArray ECB<CIPHER_TYPE,PADDING_TYPE>::encrypt(Bytes* plain, size_t plainLen, Bytes*)
        {
            ByteArray padded = this->PaddingScheme->AddPadding(plain,plainLen,this->Encryption->BLOCK_SIZE);

            Bytes* cipher = new Bytes[padded.length];
            for(size_t i=0; i<padded.length; i+=this->Encryption->BLOCK_SIZE)
            {
                this->Encryption->EncryptBlock(padded.array+i,cipher+i);
            }

            return ByteArray(cipher,padded.length);
        }

        template<typename CIPHER_TYPE, typename PADDING_TYPE>
        ByteArray ECB<CIPHER_TYPE,PADDING_TYPE>::decrypt(Bytes* cipher, size_t cipherLen, Bytes*)
        {
            ByteArray recovered;
            recovered.array = new Bytes[cipherLen];
            recovered.length = cipherLen;

            for(size_t i=0; i<cipherLen; i+=this->Encryption->BLOCK_SIZE)
            {
                this->Encryption->DecryptBlock(cipher+i,recovered.array+i);
            }

            return this->PaddingScheme->RemovePadding(recovered.array,recovered.length,this->Encryption->BLOCK_SIZE);
        }
    }
}

#endif