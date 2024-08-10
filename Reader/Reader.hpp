#pragma once

#include <cstdint>
#include <cstddef>

struct __sFILE;

class Reader
{
    private:
        __sFILE *handle = nullptr;

    public:
        Reader() = default;
        ~Reader();

        // Handle management

        bool IsFileOpen() const;

        bool OpenFile(const char *file);
        void CloseFile();

        // File size

        size_t FileSize();

        // Reading

        void ReadBytes(void *buffer, size_t off, size_t count);

        template <typename T> void Read(T *buffer, size_t off, size_t count = 1)
        { ReadBytes(buffer, off, sizeof(T) * count); }

        uint8_t Read8(size_t off);
        uint16_t Read16(size_t off);
        uint32_t Read32(size_t off);
        uint64_t Read64(size_t off);
};