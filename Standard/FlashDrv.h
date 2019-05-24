//
// Created by xudehua on 2019-05-24.
//

#ifndef STANDARDDRIVER_FLASHDRV_H
#define STANDARDDRIVER_FLASHDRV_H

#include "stdio.h"
#include "Memory.h"

#define OFFSET(address, size)                   ((address) & (((size) - 1)))

namespace Standard {

    /**
     *
     * @tparam DrvHandler
     *  Erase(uint32_t)
     *  WriteSector(uint32_t, const uint8_t *, int32_t)
     *  ReadAll(uint32_t, void *, int32_t)
     * @tparam SectorSize
     */
    template<typename DrvHandler, int32_t SectorSize>
    class FlashDrv {
    public:
        bool WriteAll(uint32_t address, const void *target, int32_t size) {
            int32_t offset = OFFSET(address, SectorSize);
            auto buffer = static_cast<const uint8_t *>(target);
            auto ret = false;
            lock_self();
            if (offset > 0) {
                int32_t remain = SectorSize - offset;
                if (remain > size) {
                    ret = writeOffsetAndCheckWithSize(address - offset, offset, buffer, size);
                    goto end;
                }
                ret = writeOffsetAndCheck(address - offset, offset, buffer);
                if (!ret) {
                    goto end;
                }
                address += SectorSize - offset;
                buffer += SectorSize - offset;
                size -= SectorSize - offset;
            }
            if (size > 0) {
                ret = writeAll_align(address, buffer, size);
            }
            end:
            unlock_self();
            return ret;
        }

    private:
        bool writeAll_align(uint32_t alignAddress, const uint8_t *target, int32_t size) {
            auto count = size / SectorSize;
            auto ret = false;
            for (int32_t i = 0; i < count; i++) {
                ret = writeAlignFullAndCheck(alignAddress, target);
                if (!ret) {
                    goto end;
                }
                alignAddress += SectorSize;
                target += SectorSize;
                size -= SectorSize;
            }
            if (size > 0) {
                ret = writeAlignAndCheckWithSize(alignAddress, target, size);
            }
            end:
            return ret;
        }

        /**
         * |******************|
         * @param alignAddress
         * @param buffer
         * @return
         */
        bool writeAlignFullAndCheck(uint32_t alignAddress, const uint8_t *buffer) {
            erase_self(alignAddress);
            writeAll_self(alignAddress, buffer);
            readAll_self(alignAddress, m_buffer_check, SectorSize);
            return MemoryEqualsWithAlign4(buffer, m_buffer_check, SectorSize);
        }

        /**
         * |**************xxxxx|
         * @param alignAddress
         * @param buffer
         * @param size
         * @return
         */
        bool writeAlignAndCheckWithSize(uint32_t alignAddress, const uint8_t *buffer, int32_t size) {
            readAll_self(alignAddress + size, m_buffer + size, SectorSize - size);
            MemoryCopy(m_buffer, buffer, size);
            return writeAlignFullAndCheck(alignAddress, m_buffer);
        }

        /**
         * |xxx***********xxxxx|
         * @param alignAddress
         * @param offset
         * @param buffer
         * @param size
         * @return
         */
        bool writeOffsetAndCheckWithSize(uint32_t alignAddress, int32_t offset, const uint8_t *buffer, int32_t size) {
            readAll_self(alignAddress, m_buffer, offset);
            readAll_self(alignAddress + offset + size, m_buffer + offset + size, SectorSize - size - offset);
            MemoryCopy(m_buffer + offset, buffer, size);
            return writeAlignFullAndCheck(alignAddress, m_buffer);
        }

        /**
         * |xxx***************|
         * @param alignAddress
         * @param offset
         * @param buffer
         * @return
         */
        bool writeOffsetAndCheck(uint32_t alignAddress, int32_t offset, const uint8_t *buffer) {
            readAll_self(alignAddress, m_buffer, offset);
            MemoryCopy(m_buffer + offset, buffer, SectorSize - offset);
            return writeAlignFullAndCheck(alignAddress, m_buffer);
        }

    private:
        inline void lock_self() {
            static_cast<DrvHandler *>(this)->Lock();
        }

        inline void unlock_self() {
            static_cast<DrvHandler *>(this)->UnLock();
        }

        inline void erase_self(uint32_t address) {
            static_cast<DrvHandler *>(this)->Erase(address);
        }

        inline void writeAll_self(uint32_t address, const uint8_t *buffer) {
            static_cast<DrvHandler *>(this)->WriteSector(address, buffer, SectorSize);
        }

        inline void readAll_self(uint32_t address, uint8_t *buffer, int32_t size) {
            static_cast<DrvHandler *>(this)->ReadAll(address, buffer, size);
        }

    private:
        uint8_t m_buffer[SectorSize];
        uint8_t m_buffer_check[SectorSize];
    };
}


#endif //STANDARDDRIVER_FLASHDRV_H
