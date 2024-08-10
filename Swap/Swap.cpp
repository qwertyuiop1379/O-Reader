#include "Swap.hpp"

// Integers

uint16_t Swap16(uint16_t n)
{
    uint16_t b1 = (n >> 8) & 0xFF;
    uint16_t b2 = n & 0xFF;
    
    return (b2 << 8) | b1;
}

uint32_t Swap32(uint32_t n)
{
    uint32_t b1 = (n >> 24) & 0xFF;
    uint32_t b2 = (n >> 16) & 0xFF;
    uint32_t b3 = (n >> 8) & 0xFF;
    uint32_t b4 = n & 0xFF;

    return (b4 << 24) | (b3 << 16) | (b2 << 8) | b1;
}

uint64_t Swap64(uint64_t n)
{
    uint64_t b1 = (n >> 56) & 0xFF;
    uint64_t b2 = (n >> 48) & 0xFF;
    uint64_t b3 = (n >> 40) & 0xFF;
    uint64_t b4 = (n >> 32) & 0xFF;
    uint64_t b5 = (n >> 24) & 0xFF;
    uint64_t b6 = (n >> 16) & 0xFF;
    uint64_t b7 = (n >> 8) & 0xFF;
    uint64_t b8 = n & 0xFF;

    return (b8 << 56) | (b7 << 48) | (b6 << 40) | (b5 << 32) | (b4 << 24) | (b3 << 16) | (b2 << 8) | b1;
}

// Mach header

void SwapMachHeader32(MachHeader32 &header)
{
    header.magic = Swap32(header.magic);
    header.cputype = Swap32(header.cputype);
    header.cpusubtype = Swap32(header.cpusubtype);
    header.filetype = Swap32(header.filetype);
    header.ncmds = Swap32(header.ncmds);
    header.sizeofcmds = Swap32(header.sizeofcmds);
    header.flags = Swap32(header.flags);
}

void SwapMachHeader64(MachHeader64 &header)
{
    header.magic = Swap32(header.magic);
    header.cputype = Swap32(header.cputype);
    header.cpusubtype = Swap32(header.cpusubtype);
    header.filetype = Swap32(header.filetype);
    header.ncmds = Swap32(header.ncmds);
    header.sizeofcmds = Swap32(header.sizeofcmds);
    header.flags = Swap32(header.flags);
    header.reserved = Swap32(header.reserved);
}

// Fat header

void SwapFatHeader(FatHeader &header)
{
    header.magic = Swap32(header.magic);
    header.narchs = Swap32(header.narchs);
}

void SwapFatArch(FatArch &arch)
{
    arch.cputype = Swap32(arch.cputype);
	arch.cpusubtype = Swap32(arch.cpusubtype);
	arch.offset = Swap32(arch.offset);
	arch.size = Swap32(arch.size);
	arch.align = Swap32(arch.align);
}