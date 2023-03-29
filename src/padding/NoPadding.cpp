#ifndef PADDING_NO_PADDING_CPP
#define PADDING_NO_PADDING_CPP

#include "../padding.hpp"
#include <iostream>

namespace Krypt {
    namespace Padding {
        const char *InvalidPadding::what() const throw() {
            return msg;
        }
        const char *InvalidPaddedLength::what() const throw() {
            return msg;
        }

        ByteArray NoPadding::AddPadding(Bytes *src, size_t len, size_t) {
            Bytes *Copy = new Bytes[len];
            memcpy(Copy, src, len);
            return ByteArray(Copy, len);
        }

        ByteArray NoPadding::RemovePadding(Bytes *src, size_t len, size_t) {
            Bytes *Copy = new Bytes[len];
            memcpy(Copy, src, len);
            return ByteArray(Copy, len);
        }
    } // namespace Padding
} // namespace Krypt

#endif