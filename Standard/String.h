//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_STRING_H
#define STANDARDDRIVER_STRING_H

#include "Memory.h"
#include <stdarg.h>
#include "ByteArray.h"

namespace Standard {

    class String {
    public:
        static int32_t GetSize(const char *string);
        static int32_t Copy(void *target, const char *source);
        static int32_t ValueOfUInt(void *target, uint32_t value, uint32_t base);
        static int32_t ValueOfInt(void *target, int32_t value);
        static void ValueOfHexByte(void *target, uint8_t value);
        static void HexStrWithByteArray(void *target, uint8_t *byteArray, int32_t size);
        static void ValueOfByteArray(void *target, ByteArray *byteArray);

    public:
        explicit String(const char *string);
        String(const String &other);
        String(String &&other) noexcept ;

        ~String();

        String& operator=(const String &other);
        String& operator=(String &&other) noexcept ;

        inline int32_t Size() const {
            return m_size;
        }

        inline const char *Content() const {
            return m_content;
        }

    private:
        int32_t m_size;
        char *m_content;
    };

}




#endif //STANDARDDRIVER_STRING_H
