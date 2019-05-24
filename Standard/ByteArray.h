//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_BYTEARRAY_H
#define STANDARDDRIVER_BYTEARRAY_H

#include <stdint.h>

struct ByteArray {
    const uint8_t *Array;
    int32_t Size;

    ByteArray(const void *memory, int32_t size) :
            Array(static_cast<const uint8_t *>(memory)),
            Size(size) {
    }
};

#endif //STANDARDDRIVER_BYTEARRAY_H
