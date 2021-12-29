# README.md
<!-- @mainpage -->

### Main

Forked From : https://github.com/SergeyBel/AES

This fork was optimized and used by my file [encryption/decryption program](https://github.com/mrdcvlsc/bethela).

**This header only library provides AES encryption and decryption algorithms, it has a portable C++ implementation and you can also activate and use the code that utilizes the AES-NI instructions.**

-----------

**Compilation Note:** This is a header only library, you only need to include the ```"Krypt.hpp"```, no need to compile the library first, and there's no need to add/link the ```.cpp``` files of the library to your compilation flag, see the example below.

***To get the peak performance of this portable library compile it with the flags ```-O3 -march=native```***

***If your system supports AES-NI instructions, just add the option ```-D USE_AESNI -maes``` in compilation to boost the performance.***

**sample program:**
```cpp
/*    sample.cpp    */
#include <iostream>
#include "src/Krypt.hpp"

using namespace Krypt;

int main()
{
    unsigned char plain[] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb
    };

    // if you want to use AES192 or AES256, just increase the size of the key to
    // 24 or 32... the AES class will automatically detect it, it will aslo throw
    // an error if the key size is not 16,24 or 32
    unsigned char aes128key[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Mode::ECB<BlockCipher::AES,Padding::ANSI_X9_23> krypt(aes128key,sizeof(aes128key));

    ByteArray cipher  = krypt.encrypt(plain,sizeof(plain));
    ByteArray recover = krypt.decrypt(cipher.array,cipher.length);
}
```

**compile with [pure c/c++ code]** ```g++ -o sample.exe sample.cpp -O3 -march=native```

**comple with [AES-NI]** ```g++ -o sample.exe sample.cpp -D USE_AESNI -maes -O3 -march=native```

-------------

<br>

**The ```Krypt``` namespace contains the following :**

| sub-namespace | sub-namespace classes |
| --- | --- |
| ```BlockCipher``` | ```AES``` |
| ```Padding``` | ```ZeroNulls```, ```ANSI_X9_23```, ```ISO_IEC_7816_4```, ```PKCS_5_7``` |
| ```Mode``` | ```ECB```, ```CBC```, ```CFB``` |

<br>

**Methods of the Classes inside the ```Mode``` namespace**
- ```encrypt()```
- ```decrypt()```

**Methods of the Classes inside the ```BlockCipher``` namespace**
- ```EncryptBlock()```
- ```DecryptBlock()```

**Methods of the Classes inside the ```Padding``` namespace**
- ```AddPadding()```
- ```RemovePadding()```

**The ```ByteArray``` class** is used to hold the output of ```encrypt()/decrypt()``` methods of the ```Mode``` classes, and the output of ```AddPadding()/RemovePadding()``` methods of the ```Padding``` classes... ```ByteArray``` methods are listed below :
- ```length``` - returns the size of the byte array
- ```array``` - returns the byte array pointer[```Krypt::Bytes* or unsigned char*```]
- ```detach()``` - returns the byte array pointer[```Krypt::Bytes* or unsigned char*```], that pointer is then dettached to the instance of the ByteArray
- ```operator<<``` - an overload for the left-shift operator
- ```operator>>``` - an overload for the right-shift operator
- ```operator[]``` - an overload for the bracket operator, use for indexing the array
