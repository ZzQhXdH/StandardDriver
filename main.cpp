#include <iostream>
#include "Standard/FormatBuilder.h"
#include "Standard/Cryptography.h"
#include "Standard/ActionBuilder.h"

class StandardOutput {

public:
    friend class Standard::FormatBuilder<StandardOutput>;

    Standard::FormatBuilder<StandardOutput> Format;
    Standard:

    StandardOutput() : Format(*this) {
    }

    void Lock() {
        std::cout << "Lock" << std::endl;
    }

    void UnLock() {
        std::cout << "UnLock" << std::endl;
    }

    void WriteAll(const void *p, int32_t size) {
        auto buffer = static_cast<const uint8_t *>(p);
        for (int32_t i = 0; i < size; i ++) {
            putchar(buffer[i]);
        }
    }

private:
    uint8_t m_buffer[500];
};

int main() {
    StandardOutput output;
    uint8_t dig[16];
    Standard::MD5Creator("1234567890", 10).Final(dig);

    auto arr = ByteArray(dig, 16);
    output.Format.format("%b\r\n", &arr);

    return 0;
}