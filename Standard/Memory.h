//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_MEMORY_H
#define STANDARDDRIVER_MEMORY_H

#include <stdint.h>

namespace Standard {

    void MemoryCopy(void *target, const void *source, uint32_t size);

    void MemorySet(void *target, uint32_t size, uint8_t value);

    bool MemoryEquals(const void *target1, const void *target2, int32_t size);

    bool MemoryEqualsWithAlign4(const void *target1, const void *target2, int32_t size);
}


#endif //STANDARDDRIVER_MEMORY_H
