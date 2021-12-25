#ifndef KRYPT_BYTEARRAY_HPP
#define KRYPT_BYTEARRAY_HPP

#include <iostream>
#include <utility>
#include "types.hpp"

namespace Krypt
{
    class ByteArray
    {
        public:

        Bytes* array;
        size_t length;

        // returns the pointer array then leaving the member .array() equal to NULL, and .length() equal to zero
        Bytes* detach();

        Bytes& operator[](size_t i);
        const Bytes& operator[](size_t i) const;
        
        ByteArray();

        ByteArray(Bytes* heap_obj, size_t length);

        // copy constructor
        ByteArray(const ByteArray& other);

        // move constructor
        ByteArray(ByteArray&& other) noexcept;

        // copy assignment
        ByteArray& operator=(const ByteArray& other);

        // move assingment
        ByteArray& operator=(ByteArray&& other) noexcept;

        ~ByteArray();
    };

    std::ostream& operator<<(std::ostream& outputStream, const ByteArray& instance);

    std::istream& operator>>(std::istream& inputStream, ByteArray& instance);
}

#include "bytearray.cpp"

#endif
