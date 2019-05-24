//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_FORMAT_H
#define STANDARDDRIVER_FORMAT_H

#include "String.h"
#include "ByteArray.h"
#include <stdio.h>

namespace Standard {

    /**
     * void Lock()
     * void UnLock()
     * m_buffer
     * void WriteWithBuffer(int32_t)
     * @tparam Writer
     */
    template <typename Writer>
    class Format {
    public:
        explicit Format(Writer &writer) :
                m_writer(writer) {
        }

        int32_t format(const char *format, ...) {
            int32_t size = 0;
            va_list ap;
            va_start(ap, format);
            char c;
            m_writer.Lock();
            while ((c = *format) != '\0') {
                if (c != '%') {
                    m_writer.m_buffer[size ++] = c;
                    format ++;
                    continue;
                }
                c = *(format + 1);
                switch (c) {
                    case 'd':
                        size += String::ValueOfInt(m_writer.m_buffer + size, va_arg(ap, int32_t));
                        format += 2;
                        break;

                    case 'x':
                        size += String::ValueOfUInt(m_writer.m_buffer + size, va_arg(ap, uint32_t), 16);
                        format += 2;
                        break;

                    case 's':
                        size += String::Copy(m_writer.m_buffer + size, va_arg(ap, const char *));
                        format += 2;
                        break;

                    case 'b': {
                        ByteArray *array = va_arg(ap, ByteArray *);
                        String::ValueOfByteArray(m_writer.m_buffer + size, array);
                        size += array->Size * 3;
                    }
                        break;
                    default:
                        format += 1;
                        m_writer.m_buffer[size ++] = '%';
                        break;
                }
            }
            m_writer.WriteWithBuffer(size);
            m_writer.UnLock();
            return size;
        }

    private:
        Writer &m_writer;
    };
}



#endif //STANDARDDRIVER_FORMAT_H
