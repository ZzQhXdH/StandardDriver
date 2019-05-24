#include <iostream>
#include "Standard/FormatBuilder.h"
#include "Standard/Cryptography.h"
#include "Standard/ActionBuilder.h"
#include "Standard/FlashDrv.h"

void printByteArray(const uint8_t *buf, uint32_t size) {
    auto count = size / 16;
    for (uint32_t i = 0; i < count; i ++) {
        for (uint32_t j = 0; j < 16; j ++) {
            printf("%02x ", buf[j + i * 16]);
        }
        size -= 16;
        printf("\r\n");
    }
    for (uint32_t j = 0; j < 16; j ++) {
        printf("%02x ", buf[j + 16 * count]);
    }
    printf("\r\n");
}

class StandardOutput : public Standard::FlashDrv<StandardOutput, 64> {

public:
    friend class Standard::FormatBuilder<StandardOutput>;
    friend class Standard::ActionBuilder<StandardOutput>;

    Standard::FormatBuilder<StandardOutput> Format;
    Standard::ActionBuilder<StandardOutput> Action;

    StandardOutput() : Format(*this), Action(*this) {
        Standard::MemorySet(m_buffer, sizeof(m_buffer), 0);
    }

    void Lock() {
     //   std::cout << "Lock" << std::endl;
    }

    void UnLock() {
       // std::cout << "UnLock" << std::endl;
    }

    void Erase(uint32_t address) {
      //  std::cout << "erase from:" << address << std::endl;
        Standard::MemorySet(m_buffer + address - OFFSET(address, 64), 64, 0xFF);
    }

    void WriteSector(uint32_t address, const uint8_t *buffer, int32_t size) {
      //  std::cout << "write from:" << address << " size:" << size << std::endl;
        Standard::MemoryCopy(m_buffer + address, buffer, size);
        //printByteArray(m_buffer, size);
    }

    void ReadAll(uint32_t address, void *buffer, int32_t size) {
       // std::cout << "read from:" << address << " size:" << size << std::endl;
        Lock();
        Standard::MemoryCopy(buffer, m_buffer + address, size);
        UnLock();
      //  printByteArray(static_cast<const uint8_t *>(buffer), size);
    }

//    void WriteAll(const void *p, int32_t size) {
//        auto buffer = static_cast<const uint8_t *>(p);
//        for (int32_t i = 0; i < size; i ++) {
//            putchar(buffer[i]);
//         //   printf("%02x ", buffer[i]);
//        }
//        printf("\r\n");
//    }

private:
    uint8_t m_buffer[500];
};



int main() {
    uint8_t buf[500];
    Standard::MemorySet(buf, sizeof(buf), 0);
    StandardOutput output;
    auto ret = output.WriteAll(65, "12345", 5);
    output.WriteAll(0, "0000", 4);
    output.WriteAll(4, "abc", 3);
    output.WriteAll(12, "0", 1);
    output.WriteAll(128, "ttttt", 5);
    output.ReadAll(0, buf, sizeof(buf));
//    std::cout << ret << std::endl;
    printByteArray(buf, sizeof(buf));
    return 0;
}