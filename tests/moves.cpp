/*    sample.cpp    */
#include <iostream>
#include "../src/Krypt.hpp"
#include "../src/bytearray.hpp"

using namespace Krypt;

int main()
{
    unsigned char plain[] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb
    };

    unsigned char aes128key[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    unsigned char IV[16] = {
        0x10, 0xa1, 0xf2, 0x0a, 0xb4, 0x55, 0x76, 0x00,
        0x8c, 0xa9, 0x8a, 0xc7, 0xcc, 0x7d, 0xee, 0xff
    };

    Mode::ECB<BlockCipher::AES,Padding::ANSI_X9_23> kryptECB(aes128key,sizeof(aes128key));
    Mode::CBC<BlockCipher::AES,Padding::ANSI_X9_23> kryptCBC(aes128key,sizeof(aes128key));
    Mode::CFB<BlockCipher::AES,Padding::ANSI_X9_23> kryptCFB(aes128key,sizeof(aes128key));

    {
        std::cout << "ECB : encrypt\n";
        ByteArray cipher  = kryptECB.encrypt(plain,sizeof(plain));
        std::cout << "ECB : decrypt\n";
        ByteArray recover = kryptECB.decrypt(cipher.array,cipher.length);

        if(memcmp(recover.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "ECB : std::pair Move to ByteArray     - Passed\n";
    

    {
        ByteArray cipher = kryptECB.encrypt(plain,sizeof(plain));
        cipher = kryptECB.decrypt(cipher.array,cipher.length);
        if(memcmp(cipher.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "ECB : std::pair Assign to ByteArray 1 - Passed\n";
    

    {
        ByteArray cipher  = kryptECB.encrypt(plain,sizeof(plain));
        ByteArray recover;
        recover = kryptECB.decrypt(cipher.array,cipher.length);
        if(memcmp(recover.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "ECB : std::pair Assign to ByteArray 2 - Passed\n";
    

    {
        ByteArray cipher  = kryptECB.encrypt(plain,sizeof(plain));
        ByteArray recover = kryptECB.decrypt(cipher.array,cipher.length);

        cipher = recover;
        if(memcmp(cipher.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "ECB : ByteArray Copied to ByteArray   - Passed\n";


    /// 

    {
        std::cout << "CBC : encrypt\n";
        ByteArray cipher  = kryptCBC.encrypt(plain,sizeof(plain),IV);
        std::cout << "CBC : decrypt\n";
        ByteArray recover = kryptCBC.decrypt(cipher.array,cipher.length,IV);
        if(memcmp(recover.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CBC : std::pair Move to ByteArray     - Passed\n";
    

    {
        ByteArray cipher = kryptCBC.encrypt(plain,sizeof(plain),IV);
        cipher = kryptCBC.decrypt(cipher.array,cipher.length,IV);
        if(memcmp(cipher.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CBC : std::pair Assign to ByteArray 1 - Passed\n";
    

    {
        ByteArray cipher  = kryptCBC.encrypt(plain,sizeof(plain),IV);
        ByteArray recover;
        recover = kryptCBC.decrypt(cipher.array,cipher.length,IV);
        if(memcmp(recover.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CBC : std::pair Assign to ByteArray 2 - Passed\n";
    

    {
        ByteArray cipher  = kryptCBC.encrypt(plain,sizeof(plain),IV);
        ByteArray recover = kryptCBC.decrypt(cipher.array,cipher.length,IV);

        cipher = recover;
        if(memcmp(cipher.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CBC : ByteArray Copied to ByteArray   - Passed\n";

    ///

    {
        std::cout << "CFB : encrypt\n";
        ByteArray cipher  = kryptCFB.encrypt(plain,sizeof(plain),IV);
        std::cout << "CFB : decrypt\n";
        ByteArray recover = kryptCFB.decrypt(cipher.array,cipher.length,IV);
        if(memcmp(recover.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CFB : std::pair Move to ByteArray     - Passed\n";
    

    {
        ByteArray cipher = kryptCFB.encrypt(plain,sizeof(plain),IV);
        cipher = kryptCFB.decrypt(cipher.array,cipher.length,IV);
        if(memcmp(cipher.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CFB : std::pair Assign to ByteArray 1 - Passed\n";
    

    {
        ByteArray cipher  = kryptCFB.encrypt(plain,sizeof(plain),IV);
        ByteArray recover;
        recover = kryptCFB.decrypt(cipher.array,cipher.length,IV);
        if(memcmp(recover.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CFB : std::pair Assign to ByteArray 2 - Passed\n";
    

    {
        ByteArray cipher  = kryptCFB.encrypt(plain,sizeof(plain),IV);
        ByteArray recover = kryptCFB.decrypt(cipher.array,cipher.length,IV);

        cipher = recover;
        if(memcmp(cipher.array,plain,sizeof(plain))) throw std::logic_error("Wrong decryption output");
    }
    std::cout << "CFB : ByteArray Copied to ByteArray   - Passed\n";
}
