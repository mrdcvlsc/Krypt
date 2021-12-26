#ifndef CFB_MODE_CPP
#define CFB_MODE_CPP

#include "../mode.hpp"

namespace Krypt::Mode
{
    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    CFB<CIPHER_TYPE,PADDING_TYPE>::CFB(const Bytes* key, size_t keyLen)
        : MODE<CIPHER_TYPE,PADDING_TYPE>()
    {
        this->Encryption = new CIPHER_TYPE(key,keyLen);
        this->PaddingScheme = new PADDING_TYPE();
    }

    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    ByteArray CFB<CIPHER_TYPE,PADDING_TYPE>::encrypt(Bytes* plain, size_t plainLen, Bytes* iv)
    {
        ByteArray padded = this->PaddingScheme->AddPadding(plain,plainLen,this->Encryption->BLOCK_SIZE);
        
        Bytes* tempIV = new Bytes[this->Encryption->BLOCK_SIZE];
        Bytes* encIV = new Bytes[this->Encryption->BLOCK_SIZE];
        Bytes* cipher = new Bytes[padded.length];

        memcpy(tempIV,iv,this->Encryption->BLOCK_SIZE);

        for(size_t i=0; i<padded.length; i+=this->Encryption->BLOCK_SIZE)
        {
            this->Encryption->EncryptBlock(tempIV,encIV);
            XorBlocks(padded.array+i,encIV,cipher+i,this->Encryption->BLOCK_SIZE);
            memcpy(tempIV, cipher+i,this->Encryption->BLOCK_SIZE);
        }
        
        delete [] tempIV;
        delete [] encIV;

        return {cipher,padded.length};
    }

    template<typename CIPHER_TYPE, typename PADDING_TYPE>
    ByteArray CFB<CIPHER_TYPE,PADDING_TYPE>::decrypt(Bytes* cipher, size_t cipherLen, Bytes* iv)
    {
        Bytes* recover = new Bytes[cipherLen];
        Bytes* tempIV = new Bytes[this->Encryption->BLOCK_SIZE];
        Bytes* encIV = new Bytes[this->Encryption->BLOCK_SIZE];

        memcpy(tempIV,iv,this->Encryption->BLOCK_SIZE);

        for(size_t i=0; i<cipherLen; i+=this->Encryption->BLOCK_SIZE)
        {
            this->Encryption->EncryptBlock(tempIV,encIV);
            XorBlocks(cipher+i,encIV,recover+i,this->Encryption->BLOCK_SIZE);
            memcpy(tempIV, cipher+i,this->Encryption->BLOCK_SIZE);
        }

        ByteArray recoverNoPadding = this->PaddingScheme->RemovePadding(recover,cipherLen,this->Encryption->BLOCK_SIZE);

        delete [] recover;
        delete [] tempIV;
        delete [] encIV;

        return recoverNoPadding;
    }
}

#endif