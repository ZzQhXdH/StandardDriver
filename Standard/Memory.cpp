//
// Created by xudehua on 2019-05-24.
//

#include "Memory.h"

namespace Standard {

    void MemoryCopy(void *target, const void *source, uint32_t size) {
        auto t = static_cast<uint8_t *>(target);
        auto s = static_cast<const uint8_t *>(source);
        while (size -- > 0) {
            *t = *s;
            t ++;
            s ++;
        }
    }

    void MemorySet(void *target, uint32_t size, uint8_t value) {
        auto t = static_cast<uint8_t *>(target);
        while (size -- > 0) {
            *t =  value;
            t ++;
        }
    }

}

