#include "Reader.hpp"

#include <cstdio>

Reader::~Reader()
{ this->CloseFile(); }

bool Reader::IsFileOpen() const
{ return this->handle != nullptr; }

bool Reader::OpenFile(const char *file)
{
    this->CloseFile();
    this->handle = fopen(file, "rb");
    
    return this->handle != nullptr;
}

void Reader::CloseFile()
{
    if (this->handle)
        fclose(this->handle);
}

size_t Reader::FileSize()
{
    if (!this->handle)
        return 0;

    fseek(this->handle, 0, SEEK_END);
    return ftell(this->handle);
}

uint8_t Reader::Read8(size_t off)
{
    uint8_t buf;
    this->Read(&buf, off);
    return buf;
}

uint16_t Reader::Read16(size_t off)
{
    uint16_t buf;
    this->Read(&buf, off);
    return buf;
}

uint32_t Reader::Read32(size_t off)
{
    uint32_t buf;
    this->Read(&buf, off);
    return buf;
}

uint64_t Reader::Read64(size_t off)
{
    uint64_t buf;
    this->Read(&buf, off);
    return buf;
}

void Reader::ReadBytes(void *buffer, size_t off, size_t count)
{
    if (!this->handle)
        return;
        
    fseek(this->handle, off, SEEK_SET);
    fread(buffer, 1, count, this->handle);
}