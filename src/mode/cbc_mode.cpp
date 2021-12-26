#ifndef CBC_MODE_CPP
#define CBC_MODE_CPP

#include "../mode.hpp"

namespace Krypt::Mode
{
    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    CBC<CIPHER_TYPE,PADDING_TYPE>::CBC(const Bytes* key, size_t keyLen)
        : MODE<CIPHER_TYPE,PADDING_TYPE>()
    {
        this->Encryption = new CIPHER_TYPE(key,keyLen);
        this->PaddingScheme = new PADDING_TYPE();
    }

    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    ByteArray CBC<CIPHER_TYPE,PADDING_TYPE>::encrypt(Bytes* plain, size_t plainLen, Bytes* iv)
    {
        ByteArray padded = this->PaddingScheme->AddPadding(plain,plainLen,this->Encryption->BLOCK_SIZE);
        Bytes* tempIV = new Bytes[this->Encryption->BLOCK_SIZE];
        Bytes* cipher = new Bytes[padded.length];

        memcpy(tempIV,iv,this->Encryption->BLOCK_SIZE);

        for(size_t i=0; i<padded.length; i+=this->Encryption->BLOCK_SIZE)
        {
            XorBlocks(tempIV,padded.array+i,tempIV,this->Encryption->BLOCK_SIZE);
            this->Encryption->EncryptBlock(tempIV,cipher+i);
            memcpy(tempIV, cipher+i,this->Encryption->BLOCK_SIZE);
        }

        delete [] tempIV;
        return {cipher,padded.length};
    }

    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    ByteArray CBC<CIPHER_TYPE,PADDING_TYPE>::decrypt(Bytes* cipher, size_t cipherLen, Bytes* iv)
    {
        Bytes* recover = new Bytes[cipherLen];
        Bytes* tempIV  = new Bytes[this->Encryption->BLOCK_SIZE];
        memcpy(tempIV,iv,this->Encryption->BLOCK_SIZE);

        for(size_t i=0; i<cipherLen; i+=this->Encryption->BLOCK_SIZE)
        {
            this->Encryption->DecryptBlock(cipher+i, recover+i);
            XorBlocks(tempIV, recover+i,recover+i,this->Encryption->BLOCK_SIZE);
            memcpy(tempIV, cipher+i,this->Encryption->BLOCK_SIZE);
        }

        ByteArray recoverNoPadding = this->PaddingScheme->RemovePadding(recover,cipherLen,this->Encryption->BLOCK_SIZE);

        delete [] tempIV;
        delete [] recover;

        return recoverNoPadding;
    }
}

#endif