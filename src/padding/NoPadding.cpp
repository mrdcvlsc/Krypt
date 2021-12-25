#ifndef PADDING_NO_PADDING_CPP
#define PADDING_NO_PADDING_CPP

#include <iostream>
#include "../padding.hpp"

namespace Krypt::Padding
{
    const char* InvalidPadding::what() const throw () { return msg; }
    const char* InvalidPaddedLength::what() const throw () { return msg; }

    std::pair<Bytes*,size_t> NoPadding::AddPadding(Bytes* src, size_t len, size_t BLOCKSIZE)
    {
        Bytes* Copy = new Bytes[len];
        memcpy(Copy,src,len);
        return {Copy,len};
    }

    std::pair<Bytes*,size_t> NoPadding::RemovePadding(Bytes* src, size_t len, size_t BLOCKSIZE)
    {
        Bytes* Copy = new Bytes[len];
        memcpy(Copy,src,len);
        return {Copy,len};
    }
}

#endif