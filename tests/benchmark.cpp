#include <iostream>
#include <chrono>
#include <random>
#include <iomanip>
#include <cmath>
#include "../src/Krypt.hpp"

using namespace Krypt;

int main() {
  const double nanosec_in_sec = 1000000000.00;

  // create random plain text
  size_t MB = 200;
  size_t bytes = MB * 1024 * 1024;

  unsigned char *plainText = new unsigned char[bytes];

  unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
  std::mt19937_64 rand_engine(seed);

  auto min = std::numeric_limits<unsigned char>::min();
  auto max = std::numeric_limits<unsigned char>::max();

  std::uniform_int_distribution<unsigned char> random_number(min, max);

  for (size_t i = 0; i < bytes; ++i) {
    plainText[i] = random_number(rand_engine);
  }

  // encryption
  unsigned char aes128Key[16] = {
    0xde, 0xed, 0xbe, 0xef, 0xca, 0xfe, 0xba, 0xbe,
    0xfe, 0xed, 0xbe, 0xef, 0xde, 0xad, 0xde, 0xed
  };

  unsigned char aes192Key[24] = {
    0xde, 0xed, 0xbe, 0xef, 0xca, 0xfe, 0xba, 0xbe,
    0xfe, 0xed, 0xbe, 0xef, 0xde, 0xad, 0xde, 0xed,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
  };

  unsigned char aes256Key[32] = {
    0xde, 0xed, 0xbe, 0xef, 0xca, 0xfe, 0xba, 0xbe,
    0xfe, 0xed, 0xbe, 0xef, 0xde, 0xad, 0xde, 0xed,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xbb
  };

  // ECB
  {
    Mode::ECB<BlockCipher::AES, Padding::ANSI_X9_23> aes128(aes128Key, sizeof(aes128Key));
    Mode::ECB<BlockCipher::AES, Padding::ANSI_X9_23> aes192(aes192Key, sizeof(aes192Key));
    Mode::ECB<BlockCipher::AES, Padding::ANSI_X9_23> aes256(aes256Key, sizeof(aes256Key));

    // ########################## AES 128 ########################## 
    auto aes128EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes128cipher = aes128.encrypt(plainText, bytes);
    auto aes128EncEnd = std::chrono::high_resolution_clock::now();
    auto aes128EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes128EncEnd - aes128EncStart);
    double aes128EncSpeed = (double) MB / (double) aes128EncDur.count();

    auto aes128DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes128recover = aes128.decrypt(aes128cipher.array, aes128cipher.length);
    auto aes128DecEnd = std::chrono::high_resolution_clock::now();
    auto aes128DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes128DecEnd - aes128DecStart);
    double aes128DecSpeed = (double) MB / (double) aes128DecDur.count();

    std::string aes128res = "success";

    if (aes128recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes128recover.array[i] != plainText[i]) {
          aes128res = "failed";
          break;
        }
      }
    } else {
      aes128res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES128 Enc | ECB | " << MB << " | " << (double) aes128EncDur.count() / nanosec_in_sec << " | " << aes128EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES128 Dec | ECB | " << MB << " | " << (double) aes128DecDur.count() / nanosec_in_sec << " | " << aes128DecSpeed * nanosec_in_sec << " mb/s | " <<  aes128res << " |\n";

    // ########################## AES 192 ########################## 
    auto aes192EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes192cipher = aes192.encrypt(plainText, bytes);
    auto aes192EncEnd = std::chrono::high_resolution_clock::now();
    auto aes192EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes192EncEnd - aes192EncStart);
    double aes192EncSpeed = (double) MB / (double) aes192EncDur.count();

    auto aes192DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes192recover = aes192.decrypt(aes192cipher.array, aes192cipher.length);
    auto aes192DecEnd = std::chrono::high_resolution_clock::now();
    auto aes192DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes192DecEnd - aes192DecStart);
    double aes192DecSpeed = (double) MB / (double) aes192DecDur.count();

    std::string aes192res = "success";

    if (aes192recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes192recover.array[i] != plainText[i]) {
          aes192res = "failed";
          break;
        }
      }
    } else {
      aes192res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES192 Enc | ECB | " << MB << " | " << (double) aes192EncDur.count() / nanosec_in_sec << " | " << aes192EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES192 Dec | ECB | " << MB << " | " << (double) aes192DecDur.count() / nanosec_in_sec << " | " << aes192DecSpeed * nanosec_in_sec << " mb/s | " <<  aes192res << " |\n";

    // ########################## AES 256 ########################## 
    auto aes256EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes256cipher = aes256.encrypt(plainText, bytes);
    auto aes256EncEnd = std::chrono::high_resolution_clock::now();
    auto aes256EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes256EncEnd - aes256EncStart);
    double aes256EncSpeed = (double) MB / (double) aes256EncDur.count();

    auto aes256DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes256recover = aes256.decrypt(aes256cipher.array, aes256cipher.length);
    auto aes256DecEnd = std::chrono::high_resolution_clock::now();
    auto aes256DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes256DecEnd - aes256DecStart);
    double aes256DecSpeed = (double) MB / (double) aes256DecDur.count();

    std::string aes256res = "success";

    if (aes256recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes256recover.array[i] != plainText[i]) {
          aes256res = "failed";
          break;
        }
      }
    } else {
      aes256res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES256 Enc | ECB | " << MB << " | " << (double) aes256EncDur.count() / nanosec_in_sec << " | " << aes256EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES256 Dec | ECB | " << MB << " | " << (double) aes256DecDur.count() / nanosec_in_sec << " | " << aes256DecSpeed * nanosec_in_sec << " mb/s | " <<  aes256res << " |\n";
  }

  // CBC
  {
    Mode::CBC<BlockCipher::AES, Padding::ANSI_X9_23> aes128(aes128Key, sizeof(aes128Key));
    Mode::CBC<BlockCipher::AES, Padding::ANSI_X9_23> aes192(aes192Key, sizeof(aes192Key));
    Mode::CBC<BlockCipher::AES, Padding::ANSI_X9_23> aes256(aes256Key, sizeof(aes256Key));

    unsigned char IV[16] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };

    // ########################## AES 128 ########################## 
    auto aes128EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes128cipher = aes128.encrypt(plainText, bytes, IV);
    auto aes128EncEnd = std::chrono::high_resolution_clock::now();
    auto aes128EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes128EncEnd - aes128EncStart);
    double aes128EncSpeed = (double) MB / (double) aes128EncDur.count();

    auto aes128DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes128recover = aes128.decrypt(aes128cipher.array, aes128cipher.length, IV);
    auto aes128DecEnd = std::chrono::high_resolution_clock::now();
    auto aes128DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes128DecEnd - aes128DecStart);
    double aes128DecSpeed = (double) MB / (double) aes128DecDur.count();

    std::string aes128res = "success";

    if (aes128recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes128recover.array[i] != plainText[i]) {
          aes128res = "failed";
          break;
        }
      }
    } else {
      aes128res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES128 Enc | CBC | " << MB << " | " << (double) aes128EncDur.count() / nanosec_in_sec << " | " << aes128EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES128 Dec | CBC | " << MB << " | " << (double) aes128DecDur.count() / nanosec_in_sec << " | " << aes128DecSpeed * nanosec_in_sec << " mb/s | " <<  aes128res << " |\n";

    // ########################## AES 192 ########################## 
    auto aes192EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes192cipher = aes192.encrypt(plainText, bytes, IV);
    auto aes192EncEnd = std::chrono::high_resolution_clock::now();
    auto aes192EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes192EncEnd - aes192EncStart);
    double aes192EncSpeed = (double) MB / (double) aes192EncDur.count();

    auto aes192DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes192recover = aes192.decrypt(aes192cipher.array, aes192cipher.length, IV);
    auto aes192DecEnd = std::chrono::high_resolution_clock::now();
    auto aes192DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes192DecEnd - aes192DecStart);
    double aes192DecSpeed = (double) MB / (double) aes192DecDur.count();

    std::string aes192res = "success";

    if (aes192recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes192recover.array[i] != plainText[i]) {
          aes192res = "failed";
          break;
        }
      }
    } else {
      aes192res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES192 Enc | CBC | " << MB << " | " << (double) aes192EncDur.count() / nanosec_in_sec << " | " << aes192EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES192 Dec | CBC | " << MB << " | " << (double) aes192DecDur.count() / nanosec_in_sec << " | " << aes192DecSpeed * nanosec_in_sec << " mb/s | " <<  aes192res << " |\n";

    // ########################## AES 256 ########################## 
    auto aes256EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes256cipher = aes256.encrypt(plainText, bytes, IV);
    auto aes256EncEnd = std::chrono::high_resolution_clock::now();
    auto aes256EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes256EncEnd - aes256EncStart);
    double aes256EncSpeed = (double) MB / (double) aes256EncDur.count();

    auto aes256DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes256recover = aes256.decrypt(aes256cipher.array, aes256cipher.length, IV);
    auto aes256DecEnd = std::chrono::high_resolution_clock::now();
    auto aes256DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes256DecEnd - aes256DecStart);
    double aes256DecSpeed = (double) MB / (double) aes256DecDur.count();

    std::string aes256res = "success";

    if (aes256recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes256recover.array[i] != plainText[i]) {
          aes256res = "failed";
          break;
        }
      }
    } else {
      aes256res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES256 Enc | CBC | " << MB << " | " << (double) aes256EncDur.count() / nanosec_in_sec << " | " << aes256EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES256 Dec | CBC | " << MB << " | " << (double) aes256DecDur.count() / nanosec_in_sec << " | " << aes256DecSpeed * nanosec_in_sec << " mb/s | " <<  aes256res << " |\n";
  }

  // CFB
  {
    Mode::CFB<BlockCipher::AES, Padding::ANSI_X9_23> aes128(aes128Key, sizeof(aes128Key));
    Mode::CFB<BlockCipher::AES, Padding::ANSI_X9_23> aes192(aes192Key, sizeof(aes192Key));
    Mode::CFB<BlockCipher::AES, Padding::ANSI_X9_23> aes256(aes256Key, sizeof(aes256Key));

    unsigned char IV[16] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };

    // ########################## AES 128 ########################## 
    auto aes128EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes128cipher = aes128.encrypt(plainText, bytes, IV);
    auto aes128EncEnd = std::chrono::high_resolution_clock::now();
    auto aes128EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes128EncEnd - aes128EncStart);
    double aes128EncSpeed = (double) MB / (double) aes128EncDur.count();

    auto aes128DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes128recover = aes128.decrypt(aes128cipher.array, aes128cipher.length, IV);
    auto aes128DecEnd = std::chrono::high_resolution_clock::now();
    auto aes128DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes128DecEnd - aes128DecStart);
    double aes128DecSpeed = (double) MB / (double) aes128DecDur.count();

    std::string aes128res = "success";

    if (aes128recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes128recover.array[i] != plainText[i]) {
          aes128res = "failed";
          break;
        }
      }
    } else {
      aes128res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES128 Enc | CFB | " << MB << " | " << (double) aes128EncDur.count() / nanosec_in_sec << " | " << aes128EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES128 Dec | CFB | " << MB << " | " << (double) aes128DecDur.count() / nanosec_in_sec << " | " << aes128DecSpeed * nanosec_in_sec << " mb/s | " <<  aes128res << " |\n";

    // ########################## AES 192 ########################## 
    auto aes192EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes192cipher = aes192.encrypt(plainText, bytes, IV);
    auto aes192EncEnd = std::chrono::high_resolution_clock::now();
    auto aes192EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes192EncEnd - aes192EncStart);
    double aes192EncSpeed = (double) MB / (double) aes192EncDur.count();

    auto aes192DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes192recover = aes192.decrypt(aes192cipher.array, aes192cipher.length, IV);
    auto aes192DecEnd = std::chrono::high_resolution_clock::now();
    auto aes192DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes192DecEnd - aes192DecStart);
    double aes192DecSpeed = (double) MB / (double) aes192DecDur.count();

    std::string aes192res = "success";

    if (aes192recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes192recover.array[i] != plainText[i]) {
          aes192res = "failed";
          break;
        }
      }
    } else {
      aes192res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES192 Enc | CFB | " << MB << " | " << (double) aes192EncDur.count() / nanosec_in_sec << " | " << aes192EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES192 Dec | CFB | " << MB << " | " << (double) aes192DecDur.count() / nanosec_in_sec << " | " << aes192DecSpeed * nanosec_in_sec << " mb/s | " <<  aes192res << " |\n";

    // ########################## AES 256 ########################## 
    auto aes256EncStart = std::chrono::high_resolution_clock::now();
    ByteArray aes256cipher = aes256.encrypt(plainText, bytes, IV);
    auto aes256EncEnd = std::chrono::high_resolution_clock::now();
    auto aes256EncDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes256EncEnd - aes256EncStart);
    double aes256EncSpeed = (double) MB / (double) aes256EncDur.count();

    auto aes256DecStart = std::chrono::high_resolution_clock::now();
    ByteArray aes256recover = aes256.decrypt(aes256cipher.array, aes256cipher.length, IV);
    auto aes256DecEnd = std::chrono::high_resolution_clock::now();
    auto aes256DecDur = std::chrono::duration_cast<std::chrono::nanoseconds>(aes256DecEnd - aes256DecStart);
    double aes256DecSpeed = (double) MB / (double) aes256DecDur.count();

    std::string aes256res = "success";

    if (aes256recover.length == bytes) {
      for (size_t i = 0; i < bytes; ++i) {
        if (aes256recover.array[i] != plainText[i]) {
          aes256res = "failed";
          break;
        }
      }
    } else {
      aes256res = "failed";
    }

    std::cout << std::fixed << std::setprecision(2) <<
    "| AES256 Enc | CFB | " << MB << " | " << (double) aes256EncDur.count() / nanosec_in_sec << " | " << aes256EncSpeed * nanosec_in_sec << " mb/s | N/A |\n";
    
    std::cout << std::fixed << std::setprecision(2) <<
    "| AES256 Dec | CFB | " << MB << " | " << (double) aes256DecDur.count() / nanosec_in_sec << " | " << aes256DecSpeed * nanosec_in_sec << " mb/s | " <<  aes256res << " |\n";
  }

  return 0;
}