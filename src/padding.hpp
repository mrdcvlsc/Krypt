#ifndef KRYPT_PADDING_HPP
#define KRYPT_PADDING_HPP

#include "types.hpp"
#include <cstring>
#include <exception>
#include <iostream>
#include <utility>

namespace Krypt {
    namespace Padding {
        class InvalidPadding : public std::exception {
            public:

            InvalidPadding(const char *info) : msg(info) {
            }
            const char *msg;
            const char *what() const throw();
        };

        class InvalidPaddedLength : public std::exception {
            public:

            InvalidPaddedLength(const char *paddingSchemName) : msg(paddingSchemName) {
            }
            const char *msg;
            const char *what() const throw();
        };

        /// default & base class for padding - pad the src with zeros.
        class NoPadding {
            public:

            /** does nothing obviously. **/
            virtual ByteArray AddPadding(Bytes *src, size_t len, size_t BLOCKSIZE);

            /** does nothing obviously. **/
            virtual ByteArray RemovePadding(Bytes *src, size_t len, size_t BLOCKSIZE);

            virtual ~NoPadding() = default;
        };

        /// default & base class for padding - pad the src with zeros.
        class ZeroNulls : public NoPadding {
            public:

            /** Pad the last block with zeros [reallocates memory].
             * @return padded ByteArray generated from src.
             * **/
            ByteArray AddPadding(Bytes *src, size_t len, size_t BLOCKSIZE);

            /** Removes the last 16 byte zeros [reallocates memory].
             * @return padded ByteArray generated from src.
             * **/
            ByteArray RemovePadding(Bytes *src, size_t len, size_t BLOCKSIZE);

            ~ZeroNulls() = default;
        };

        class ANSI_X9_23 : public NoPadding {
            public:

            /** Pad the `src` with zeros first, then sets the last byte value to the count of paddings added
             * [reallocates memory].
             * @return padded ByteArray generated from src.
             * **/
            ByteArray AddPadding(Bytes *src, size_t len, size_t BLOCKSIZE) override;

            /** Removes the number of bytes [reallocates memory].
             * @returns padded ByteArray generated from src.
             * **/
            ByteArray RemovePadding(Bytes *src, size_t len, size_t BLOCKSIZE) override;

            ~ANSI_X9_23() {
            }
        };

        class ISO_IEC_7816_4 : public NoPadding {
            public:

            /** Adds one `0x80` byte value, then pad the next remaining spaces with zeros [reallocates memory].
             * @return padded ByteArray generated from src.
             * **/
            ByteArray AddPadding(Bytes *src, size_t len, size_t BLOCKSIZE) override;

            /** removes padding [reallocates memory].
             * - figures out the padding size by checking the sequence of zeros from the least significant to the most
             * significant byte until it hits `0x80` byte value.
             * @return padded ByteArray generated from src.
             * **/
            ByteArray RemovePadding(Bytes *src, size_t len, size_t BLOCKSIZE) override;

            ~ISO_IEC_7816_4() {
            }
        };

        class PKCS_5_7 : public NoPadding {
            public:

            /** Pad the `src` with the value of the padding count itself [reallocates memory].
             * @return the new length of the padded `src`.
             * **/
            ByteArray AddPadding(Bytes *src, size_t len, size_t BLOCKSIZE) override;

            /** removes padding [reallocates memory].
             * - figures out the padding size by getting the value of the last byte.
             * @return the new length of the un-padded `src`.
             * **/
            ByteArray RemovePadding(Bytes *src, size_t len, size_t BLOCKSIZE) override;

            ~PKCS_5_7() {
            }
        };
    } // namespace Padding
} // namespace Krypt

#include "padding/ANSI_X9_23.cpp"
#include "padding/ISO_IEC_7816_4.cpp"
#include "padding/NoPadding.cpp"
#include "padding/PKCS_5_7.cpp"
#include "padding/ZeroPadding.cpp"

#endif
