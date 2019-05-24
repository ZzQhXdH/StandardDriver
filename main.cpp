#include <iostream>
#include "Standard/Format.h"

class StandardOutput {

public:
    friend class Standard::Format<StandardOutput>;

    Standard::Format<StandardOutput> Format;

    StandardOutput() : Format(*this) {
    }

    void Lock() {
        std::cout << "Lock" << std::endl;
    }

    void UnLock() {
        std::cout << "UnLock" << std::endl;
    }

    void WriteWithBuffer(int32_t size) {
        for (int32_t i = 0; i < size; i ++) {
            putchar(m_buffer[i]);
        }
    }

private:
    uint8_t m_buffer[500];
};

int main() {
    StandardOutput output;
    auto arr = ByteArray("ASDFG", 5);
    output.Format.format("%s,%d,%x,%s,%d,%b\r\n", "Hello Word", 123, 0x543, "231", -342, &arr);

    return 0;
}