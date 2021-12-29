# How to Use

@tableofcontents

------------

### [1] First we need to include the main header file

```cpp
#include "Krypt.hpp"
```

------------

### [1.5] It Would also be nice to use the Krypt namespace right way to reduce the length of the line of code when instantiating our classes later

```cpp
using namespace Krypt;
```

------------

### [2] Choose your encryption setup

Before encrypting or decrypting you need to do the following first.
  1. **choose a mode of encryption**, currently this library can only offer ```ECB```, ```CBC``` and ```CFB``` all of this class is in the ```Mode``` namespace.
  2. **choose a block cipher**, currently this library has only one block cipher and that is ```AES```, it is inside the ```BlockCipher``` namespace.
  3. **choose a padding scheme**, as of now this library has ```ANSI_X9_23```, ```ISO_IEC_7816_4```, ```PKCS_5_7``` and ```ZeroPadding```, all of this padding classes are inside the ```Padding``` namespace.

------------

### [3] Creating an encryption class

For starters you need an encryption object to start encrypting and decrypting byte arrays.

Let's use the ```ECB``` mode of encryption, the ```AES``` as the blockcipher and ```PKCS_5_7``` for our padding, to instantiate our encryption object, we also need a key for our object.

```cpp
#define KEYLEN 16

unsigned char AES128KEY[KEYLEN] = {
    0x00, 0xa2, 0xff, 0x3c, 0xd4, 0x11, 0x2e, 0x02,
    0x21, 0x2f, 0x54, 0xa7, 0xaf, 0xec, 0x01, 0x32
};

Mode::ECB<BlockCipher::AES,Padding::PKCS_5_7> krypt(AES128KEY,KEYLEN);
```

For AES192 a key with 24 elements is needed.

For AES256 a key with 32 elements is needed.

For other ```Mode```s like ```CBC``` and ```CFB``` an ```unsigned char *iv``` array is needed in the instantiation as a third argument, the length of the iv should match the length of the block size of the blockcipher, for AES this would be 16.

------------

### [4] Encrypting and Decrypting

Now to encrypt and decrypt a byte array just use the ```encrypt()``` and ```decrypt()``` method.

```cpp
#define PLAINLEN 11

unsigned char plain[] = {
    0x00, 0x1a, 0x22, 0xb3, 0x4c, 0x13, 0xb6, 0xbb,
    0xf0, 0x11, 0x2a
};

ByteArray cipher  = krypt.encrypt(plain,PLAINLEN);
ByteArray recover = krypt.decrypt(cipher.array,cipher.length);
```

------------

### [4.5] Let's Print the Outputs

```cpp
std::cout << "Plain   : ";
printHexArray(plain,PLAINLEN);

std::cout << "Cipher  : ";
printHexArray(cipher.array,cipher.length);

std::cout << "Recover : ";
printHexArray(recover.array,recover.length);
```

**output**
```shell
Plain   : 00 1a 22 b3 4c 13 b6 bb f0 11 2a 
Cipher  : 36 84 82 36 4f c4 d9 10 22 74 21 9a dc a5 ff eb 
Recover : 00 1a 22 b3 4c 13 b6 bb f0 11 2a
```
------------

**See the whole sample sorce file in Krypt/docs/samples/ecb.cpp**

- compile using portable C++ code and looping
    - g++ ecb.cpp -o ecb -O2

- compile using AES-NI [huge performance boost is AES-NI is supported]
    - g++ ecb.cpp -o ecb -D USE_AESNI -O2 -maes