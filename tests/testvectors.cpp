#include <iostream>
#include <vector>
#include "small_test.hpp"
#include "../src/Krypt.hpp"

const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);

int main() {
  smlts::test t;

  // ############# BLOCK CIPHER ###############3

  // TEST(BlockCipher, AES128)
  {
    unsigned char plain[BLOCK_BYTES_LENGTH] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };

    unsigned char key[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    unsigned char cipherTarget[] = {
      0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
      0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a
    };

    unsigned char
      *cipher = new unsigned char[BLOCK_BYTES_LENGTH],
      *recover = new unsigned char[BLOCK_BYTES_LENGTH];

    Krypt::BlockCipher::AES aes(key,sizeof(key));
    aes.EncryptBlock(plain,cipher);
    aes.DecryptBlock(cipher,recover);

    t.byte_eq(plain,recover,BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES128)");
    t.byte_eq(cipher, cipherTarget, BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES128) : cipher");

    delete [] cipher;
    delete [] recover;
  }

  // TEST(BlockCipher, AES192)
  {
    unsigned char plain[BLOCK_BYTES_LENGTH] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };

    unsigned char key[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
    };

    unsigned char cipherTarget[] = {
      0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0,
      0x6e, 0xaf, 0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91
    };

    unsigned char
      *cipher = new unsigned char[BLOCK_BYTES_LENGTH],
      *recover = new unsigned char[BLOCK_BYTES_LENGTH];

    Krypt::BlockCipher::AES aes(key,sizeof(key));
    aes.EncryptBlock(plain,cipher);
    aes.DecryptBlock(cipher,recover);

    t.byte_eq(plain,recover,BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES192)");
    t.byte_eq(cipher, cipherTarget, BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES192) : cipher");

    delete [] cipher;
    delete [] recover;
  }

  // TEST(BlockCipher, AES256)
  {
    unsigned char plain[BLOCK_BYTES_LENGTH] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };

    unsigned char key[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
      0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    unsigned char cipherTarget[] = {
      0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf,
      0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89
    };

    unsigned char
      *cipher = new unsigned char[BLOCK_BYTES_LENGTH],
      *recover = new unsigned char[BLOCK_BYTES_LENGTH];

    Krypt::BlockCipher::AES aes(key,sizeof(key));
    aes.EncryptBlock(plain,cipher);
    aes.DecryptBlock(cipher,recover);

    t.byte_eq(plain,recover,BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES256)");
    t.byte_eq(cipher, cipherTarget, BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES256) : cipher");

    delete [] cipher;
    delete [] recover;
  }

  // ############# PADDING ###############3

  // TEST(Padding, LENGTH_4TO8_ZeroNulls)
  {
    unsigned char plain[] = {
        0x00, 0x11, 0x22, 0x33
    };

    unsigned char padded_plain[] = {
        0x00, 0x11, 0x22, 0x33, 0x00, 0x00, 0x00, 0x00
    };

    Krypt::Padding::ZeroNulls padding;

    unsigned char *heap_plain = new unsigned char[sizeof(plain)];
    memcpy(heap_plain,plain,sizeof(plain));

    Krypt::ByteArray padded = padding.AddPadding(heap_plain,sizeof(plain),8);
    t.byte_eq(padded.array,padded_plain,padded.length, "TEST(Padding, LENGTH_4TO8_ZeroNulls)");

    Krypt::ByteArray recover = padding.RemovePadding(padded.array,padded.length,8);
    t.byte_eq(recover.array,plain,recover.length, "TEST(Padding, LENGTH_4TO8_ZeroNulls)");

    delete [] heap_plain;
  }

  // TEST(Padding, LENGTH_4TO8_PKCS_5_7)
  {
    unsigned char plain[] = {
        0x00, 0x11, 0x22, 0x33
    };

    unsigned char padded_plain[] = {
        0x00, 0x11, 0x22, 0x33, 0x04, 0x04, 0x04, 0x04
    };

    Krypt::Padding::PKCS_5_7 padding;

    unsigned char *heap_plain = new unsigned char[sizeof(plain)];
    memcpy(heap_plain,plain,sizeof(plain));

    Krypt::ByteArray padded = padding.AddPadding(heap_plain,sizeof(plain),8);
    t.byte_eq(padded.array,padded_plain,padded.length, "TEST(Padding, LENGTH_4TO8_PKCS_5_7) padded");

    Krypt::ByteArray recover = padding.RemovePadding(padded.array,padded.length,8);
    t.byte_eq(recover.array,plain,recover.length, "TEST(Padding, LENGTH_4TO8_PKCS_5_7)");

    delete [] heap_plain;
  }

  // TEST(Padding, LENGTH_4TO8_ISO_IEC_7816_4)
  {
    unsigned char plain[] = {
        0x00, 0x11, 0x22, 0x33
    };

    unsigned char padded_plain[] = {
        0x00, 0x11, 0x22, 0x33, 0x80, 0x00, 0x00, 0x00
    };

    Krypt::Padding::ISO_IEC_7816_4 padding;

    unsigned char *heap_plain = new unsigned char[sizeof(plain)];
    memcpy(heap_plain,plain,sizeof(plain));

    Krypt::ByteArray padded = padding.AddPadding(heap_plain,sizeof(plain),8);
    t.byte_eq(padded.array,padded_plain,padded.length, "TEST(Padding, LENGTH_4TO8_ISO_IEC_7816_4) padded");

    Krypt::ByteArray recover = padding.RemovePadding(padded.array,padded.length,8);
    t.byte_eq(recover.array,plain,recover.length, "TEST(Padding, LENGTH_4TO8_ISO_IEC_7816_4)");

    delete [] heap_plain;
  }

  // TEST(Padding, LENGTH_4TO8_ANSI_X9_23)
  {
    unsigned char plain[] = {
        0x00, 0x11, 0x22, 0x33
    };

    unsigned char padded_plain[] = {
        0x00, 0x11, 0x22, 0x33, 0x00, 0x00, 0x00, 0x04
    };

    Krypt::Padding::ANSI_X9_23 padding;

    unsigned char *heap_plain = new unsigned char[sizeof(plain)];
    memcpy(heap_plain,plain,sizeof(plain));

    Krypt::ByteArray padded = padding.AddPadding(heap_plain,sizeof(plain),8);
    t.byte_eq(padded.array,padded_plain,padded.length, "TEST(Padding, LENGTH_4TO8_ANSI_X9_23) padded");

    Krypt::ByteArray recover = padding.RemovePadding(padded.array,padded.length,8);
    t.byte_eq(recover.array,plain,recover.length, "TEST(Padding, LENGTH_4TO8_ANSI_X9_23)");

    delete [] heap_plain;
  }

  // #####################################################################
  // ######################### MODE ECB - AES128 #########################
  // #####################################################################

  // TEST(ModeECB, ECB_ZeroNulls_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ZeroNulls_AES128)");
  }

  // TEST(ModeECB, ECB_PKCS_5_7_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_PKCS_5_7_AES128)");
  }

  // TEST(ModeECB, ECB_ISO_IEC_7816_4_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ISO_IEC_7816_4_AES128)");
  }

  // TEST(ModeECB, ECB_ANSI_X9_23_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ANSI_X9_23_AES128)");
  }

  // ######################### MODE ECB - AES192 #########################

  // TEST(ModeECB, ECB_ZeroNulls_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ZeroNulls_AES192)");
  }

  // TEST(ModeECB, ECB_PKCS_5_7_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_PKCS_5_7_AES192)");
  }

  // TEST(ModeECB, ECB_ISO_IEC_7816_4_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ISO_IEC_7816_4_AES192)");
  }

  // TEST(ModeECB, ECB_ANSI_X9_23_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ANSI_X9_23_AES192)");
  }

  // ######################### MODE ECB - AES256 #########################

  // TEST(ModeECB, ECB_ZeroNulls_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ZeroNulls_AES256)");
  }

  // TEST(ModeECB, ECB_PKCS_5_7_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_PKCS_5_7_AES256)");
  }

  // TEST(ModeECB, ECB_ISO_IEC_7816_4_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ISO_IEC_7816_4_AES256)");
  }

  // TEST(ModeECB, ECB_ANSI_X9_23_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Mode::ECB<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain));
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeECB, ECB_ANSI_X9_23_AES256)");
  }

  // #####################################################################
  // ######################### MODE CBC - AES128 #########################
  // #####################################################################

  // TEST(ModeCBC, CBC_ZeroNulls_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ZeroNulls_AES128)");
  }

  // TEST(ModeCBC, CBC_PKCS_5_7_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_PKCS_5_7_AES128)");
  }

  // TEST(ModeCBC, CBC_ISO_IEC_7816_4_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ISO_IEC_7816_4_AES128)");
  }

  // TEST(ModeCBC, CBC_ANSI_X9_23_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ANSI_X9_23_AES128)");
  }

  // ######################### MODE CBC - AES192 #########################

  // TEST(ModeCBC, CBC_ZeroNulls_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ZeroNulls_AES192)");
  }

  // TEST(ModeCBC, CBC_PKCS_5_7_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_PKCS_5_7_AES192)");
  }

  // TEST(ModeCBC, CBC_ISO_IEC_7816_4_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ISO_IEC_7816_4_AES192)");
  }

  // TEST(ModeCBC, CBC_ANSI_X9_23_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ANSI_X9_23_AES192)");
  }

  // ######################### MODE CBC - AES256 #########################

  // TEST(ModeCBC, CBC_ZeroNulls_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ZeroNulls_AES256)");
  }

  // TEST(ModeCBC, CBC_PKCS_5_7_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_PKCS_5_7_AES256)");
  }

  // TEST(ModeCBC, CBC_ISO_IEC_7816_4_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ISO_IEC_7816_4_AES256)");
  }

  // TEST(ModeCBC, CBC_ANSI_X9_23_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CBC<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCBC, CBC_ANSI_X9_23_AES256)");
  }

  // #####################################################################
  // ######################### MODE CFB - AES128 #########################
  // #####################################################################

  // TEST(ModeCFB, CFB_ZeroNulls_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ZeroNulls_AES128)");
  }

  // TEST(ModeCFB, CFB_PKCS_5_7_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_PKCS_5_7_AES128)");
  }

  // TEST(ModeCFB, CFB_ISO_IEC_7816_4_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ISO_IEC_7816_4_AES128)");
  }

  // TEST(ModeCFB, CFB_ANSI_X9_23_AES128)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ANSI_X9_23_AES128)");
  }

  // ######################### MODE CFB - AES192 #########################

  // TEST(ModeCFB, CFB_ZeroNulls_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ZeroNulls_AES192)");
  }

  // TEST(ModeCFB, CFB_PKCS_5_7_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_PKCS_5_7_AES192)");
  }

  // TEST(ModeCFB, CFB_ISO_IEC_7816_4_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ISO_IEC_7816_4_AES192)");
  }

  // TEST(ModeCFB, CFB_ANSI_X9_23_AES192)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ANSI_X9_23_AES192)");
  }

  // ######################### MODE CFB - AES256 #########################

  // TEST(ModeCFB, CFB_ZeroNulls_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ZeroNulls> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ZeroNulls_AES256)");
  }

  // TEST(ModeCFB, CFB_PKCS_5_7_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::PKCS_5_7> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_PKCS_5_7_AES256)");
  }

  // TEST(ModeCFB, CFB_ISO_IEC_7816_4_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ISO_IEC_7816_4> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ISO_IEC_7816_4_AES256)");
  }

  // TEST(ModeCFB, CFB_ANSI_X9_23_AES256)
  {
    Krypt::Bytes plain[] = {
        0x00, 0x01, 0xa2, 0xb3, 0xff, 0x74, 0x32, 0xcd
    };

    Krypt::Bytes aeskey[] = {
      0xa0, 0xb1, 0x02, 0x03, 0xd4, 0x05, 0xf6, 0xa7,
      0x08, 0xc9, 0x0a, 0x0b, 0x0c, 0xed, 0x0e, 0xff,
      0xfc, 0xed, 0x0e, 0x0f, 0x04, 0x05, 0x16, 0x87,
      0x00, 0xaa, 0x33, 0x80, 0xed, 0xf2, 0x33, 0x43
    };

    Krypt::Bytes iv[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    Krypt::Mode::CFB<Krypt::BlockCipher::AES,Krypt::Padding::ANSI_X9_23> EncScheme(aeskey,sizeof(aeskey));
    Krypt::ByteArray encrypted = EncScheme.encrypt(plain,sizeof(plain),iv);
    Krypt::ByteArray decrypted = EncScheme.decrypt(encrypted.array,encrypted.length,iv);

    t.byte_eq(decrypted.array,plain,decrypted.length, "TEST(ModeCFB, CFB_ANSI_X9_23_AES256)");
  }

  return t.get_final_verdict();
}