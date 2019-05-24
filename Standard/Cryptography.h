//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_CRYPTOGRAPHY_H
#define STANDARDDRIVER_CRYPTOGRAPHY_H

#include <stdint.h>

namespace Standard {

    uint16_t CryptographyWithCrc16(const void *target, int32_t size);

    class MD5Creator {
    public:
        MD5Creator();

        MD5Creator(const void *input, int32_t size);

        MD5Creator& Update(const void *input, int32_t size);

        void Final(uint8_t digest[16]);

    private:
        uint32_t count[2];
        uint32_t state[4];
        uint8_t buffer[64];
        uint32_t x[64];
        uint8_t bits[8];
    };

}

#endif //STANDARDDRIVER_CRYPTOGRAPHY_H
