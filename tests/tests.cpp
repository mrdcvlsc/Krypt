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
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xaa
    };

    unsigned char key[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
    };

    unsigned char
      *cipher = new unsigned char[BLOCK_BYTES_LENGTH],
      *recovr = new unsigned char[BLOCK_BYTES_LENGTH];

    Krypt::BlockCipher::AES aes(key,sizeof(key));
    aes.EncryptBlock(plain,cipher);
    aes.DecryptBlock(cipher,recovr);

    t.byte_eq(plain,recovr,BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES128)");

    delete [] cipher;
    delete [] recovr;
  }

  // TEST(BlockCipher, AES192)
  {
    unsigned char plain[BLOCK_BYTES_LENGTH] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xaa
    };

    unsigned char key[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
      0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b
    };

    unsigned char
      *cipher = new unsigned char[BLOCK_BYTES_LENGTH],
      *recovr = new unsigned char[BLOCK_BYTES_LENGTH];

    Krypt::BlockCipher::AES aes(key,sizeof(key));
    aes.EncryptBlock(plain,cipher);
    aes.DecryptBlock(cipher,recovr);
    t.byte_eq(plain,recovr,BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES192)");

    delete [] cipher;
    delete [] recovr;
  }

  // TEST(BlockCipher, AES256)
  {
    unsigned char plain[BLOCK_BYTES_LENGTH] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xaa
    };

    unsigned char key[] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
      0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
      0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0xf7
    };

    unsigned char
      *cipher = new unsigned char[BLOCK_BYTES_LENGTH],
      *recovr = new unsigned char[BLOCK_BYTES_LENGTH];

    Krypt::BlockCipher::AES aes(key,sizeof(key));
    aes.EncryptBlock(plain,cipher);
    aes.DecryptBlock(cipher,recovr);
    t.byte_eq(plain,recovr,BLOCK_BYTES_LENGTH, "TEST(BlockCipher, AES256)");

    delete [] cipher;
    delete [] recovr;
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