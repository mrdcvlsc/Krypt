#ifndef AES_CONFIG_HPP
#define AES_CONFIG_HPP

// WIP

#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__)
#include <immintrin.h>
#include <xmmintrin.h>
#define AES_IMPLEMENT_INTEL_AESNI
#elif defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM)
#if defined(__GNUC__)
    #include <stdint.h>
#endif

#if defined(__ARM_NEON) || defined(_MSC_VER)
    #include <arm_neon.h>
#endif

/* GCC and LLVM Clang, but not Apple Clang */
#if defined(__GNUC__) && !defined(__apple_build_version__)
    #if defined(__ARM_ACLE) || defined(__ARM_FEATURE_CRYPTO)
        #include <arm_acle.h>
    #endif
#endif
#define AES_IMPLEMENT_ARM_NEON
#else
#define AES_IMPLEMENT_PORTABLE_CPLUSPLUS
#endif

#if defined(USE_AES_ARM_NEON)
#undef AES_IMPLEMENT_INTEL_AESNI
#undef AES_IMPLEMENT_PORTABLE_CPLUSPLUS
#elif defined(USE_AES_INTEL_AESNI)
#undef AES_IMPLEMENT_ARM_NEON
#undef AES_IMPLEMENT_PORTABLE_CPLUSPLUS
#else
#undef AES_IMPLEMENT_ARM_NEON
#undef AES_IMPLEMENT_INTEL_AESNI
#endif

#endif