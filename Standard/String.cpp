//
// Created by xudehua on 2019-05-24.
//

#include "String.h"
#include "TemplateUtil.h"

namespace Standard {

    static const char HexList[] = {
            '0', '1', '2', '3',
            '4', '5', '6', '7',
            '8', '9', 'A', 'B',
            'C', 'D', 'E', 'F',
    };

    int32_t String::GetSize(const char *string) {
        int32_t size = 0;
        while (*string != '\0') {
            size++;
            string++;
        }
        return size;
    }

    int32_t String::Copy(void *target, const char *source) {
        char *t = static_cast<char *>(target);
        int32_t size = 0;
        while (*source != '\0') {
            *t = *source;
            t++;
            source++;
            size++;
        }
        *t = '\0';
        return size;
    }

    int32_t String::ValueOfUInt(void *target, uint32_t value, uint32_t base) {
        int32_t size = 1;
        uint32_t temp = value;
        char *t = static_cast<char *>(target);
        while (temp /= base) {
            size++;
        }
        for (int32_t i = 0; i < size; i++) {
            t[size - 1 - i] = HexList[value % base];
            value /= base;
        }
        return size;
    }

    int32_t String::ValueOfInt(void *target, int32_t value) {
        if (value < 0) {
            auto t = static_cast<char *>(target);
            *t = '-';
            t++;
            return ValueOfUInt(t, -value, 10) + 1;
        }
        return ValueOfUInt(target, value, 10);
    }

    void String::ValueOfHexByte(void *target, uint8_t value) {
        auto t = static_cast<char *>(target);
        *t = HexList[value >> 4];
        t++;
        *t = HexList[value & 0x0F];
        t++;
        *t = ' ';
    }

    void String::HexStrWithByteArray(void *target, uint8_t *byteArray, int32_t size) {
        auto t = static_cast<char *>(target);
        for (int32_t i = 0; i < size; i++) {
            ValueOfHexByte(t, byteArray[i]);
            t += 3;
        }
    }

    void String::ValueOfByteArray(void *target, ByteArray *byteArray) {
        auto t = static_cast<char *>(target);
        for (int32_t i = 0; i < byteArray->Size; i++) {
            ValueOfHexByte(t, byteArray->Array[i]);
            t += 3;
        }
    }

    String::String(const char *string) :
            m_size(GetSize(string)),
            m_content(new char[m_size + 1]) {
        MemoryCopy(m_content, string, m_size + 1);
    }

    String::String(const String &other) :
            m_size(other.m_size),
            m_content(new char[m_size + 1]) {
        MemoryCopy(m_content, other.m_content, m_size + 1);
    }

    String::String(Standard::String &&other) noexcept :
            m_size(other.m_size),
            m_content(other.m_content) {
        other.m_content = nullptr;
    }

    String::~String() {
        if (m_content == nullptr) {
            return;
        }
        delete[] m_content;
    }

    String &String::operator=(const String &other) {
        delete[] m_content;
        m_size = other.m_size;
        m_content = new char[m_size + 1];
        MemoryCopy(m_content, other.m_content, m_size + 1);
        return *this;
    }

    String &String::operator=(Standard::String &&other) noexcept {
        Swap(m_size, other.m_size);
        Swap(m_content, other.m_content);
        return *this;
    }


}
