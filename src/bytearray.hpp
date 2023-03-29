#ifndef KRYPT_BYTEARRAY_HPP
#define KRYPT_BYTEARRAY_HPP

#include "types.hpp"
#include <iostream>
#include <utility>

namespace Krypt {
    class ByteArray {
        public:

        /// this is the Bytes* or unsigned char* that contains the elements of the array
        Bytes *array;

        /// the total element of the in the array
        size_t length;

        /// detach the heap allocated pointer inside of the ByteArray class instance.
        /// @return raw pointer of unsigned char* or Bytes*.
        Bytes *detach();

        Bytes &operator[](size_t i);
        const Bytes &operator[](size_t i) const;

        ByteArray();

        ByteArray(Bytes *heap_obj, size_t length);

        // copy constructor
        ByteArray(const ByteArray &other);

        // move constructor
        ByteArray(ByteArray &&other) noexcept;

        // copy assignment
        ByteArray &operator=(const ByteArray &other);

        // move assingment
        ByteArray &operator=(ByteArray &&other) noexcept;

        ~ByteArray();
    };

    std::ostream &operator<<(std::ostream &outputStream, const ByteArray &instance);

    std::istream &operator>>(std::istream &inputStream, ByteArray &instance);
} // namespace Krypt

#include "bytearray.cpp"

#endif
