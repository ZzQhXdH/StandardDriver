//
// Created by xudehua on 2019-05-24.
//

#include "Memory.h"

namespace Standard {

    void MemoryCopy(void *target, const void *source, uint32_t size) {
        auto t = static_cast<uint8_t *>(target);
        auto s = static_cast<const uint8_t *>(source);
        while (size-- > 0) {
            *t = *s;
            t++;
            s++;
        }
    }

    void MemorySet(void *target, uint32_t size, uint8_t value) {
        auto t = static_cast<uint8_t *>(target);
        while (size-- > 0) {
            *t = value;
            t++;
        }
    }

    bool MemoryEquals(const void *target1, const void *target2, int32_t size) {
        auto t1 = static_cast<const uint8_t *>(target1);
        auto t2 = static_cast<const uint8_t *>(target2);
        while (size-- > 0) {
            if (*t1 != *t2) {
                return false;
            }
        }
        return true;
    }

    bool MemoryEqualsWithAlign4(const void *target1, const void *target2, int32_t size) {
        size /=  4;
        auto t1 = static_cast<const uint32_t *>(target1);
        auto t2 = static_cast<const uint32_t *>(target2);
        while (size-- > 0) {
            if (*t1 != *t2) {
                return false;
            }
        }
        return true;
    }

}

