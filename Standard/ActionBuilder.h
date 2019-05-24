//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_ACTIONBUILDER_H
#define STANDARDDRIVER_ACTIONBUILDER_H

#include <stdint.h>

namespace Standard {

    template <typename Writer>
    class ActionBuilder {
    public:
        explicit ActionBuilder(Writer &writer) : m_action(0), m_size(0), m_writer(writer) {
        }

        ActionBuilder &setAction(uint8_t action) {
            m_writer.Lock();
            m_action = action;
            return *this;
        }

        void buildAndWrite() {
            int32_t size = builder(m_writer.m_buffer + m_size);
            m_writer.WriteAll(m_writer.m_buffer + m_size, size);
            m_writer.UnLock();
        }

        ActionBuilder &appendByte(uint8_t byte) {
            m_writer.m_buffer[m_size ++] = byte;
            return *this;
        }

        ActionBuilder &appendShort(uint16_t value) {
            m_writer.m_buffer[m_size ++] = (value >> 7) & 0x7F;
            m_writer.m_buffer[m_size ++] = value & 0x7F;
            return *this;
        }

        ActionBuilder &appendInt(uint32_t value) {
            m_writer.m_buffer[m_size ++] = (value >> 21) & 0x7F;
            m_writer.m_buffer[m_size ++] = (value >> 14) & 0x7F;
            m_writer.m_buffer[m_size ++] = (value >> 7) & 0x7F;
            m_writer.m_buffer[m_size ++] = value & 0x7F;
            return *this;
        }

    private:
        int32_t builder(uint8_t *buffer) {
            int32_t size = m_size + 5;
            buffer[0] = 0xE1;
            buffer[1] = size;
            buffer[2] = m_action;
            uint8_t c = 0;
            for (int32_t i = 0; i < m_size; i ++) {
                buffer[3 + i] = m_writer.m_buffer[i];
                c ^= m_writer.m_buffer[i];
            }
            buffer[3 + m_size] = c;
            buffer[4 + m_size] = 0xEF;
            return size;
        }

    private:
        uint8_t m_action;
        int32_t m_size;
        Writer &m_writer;
    };
}


#endif //STANDARDDRIVER_ACTIONBUILDER_H
