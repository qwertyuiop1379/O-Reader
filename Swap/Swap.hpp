#pragma once

#include <Mach-O/Mach-O.hpp>

// Integers

uint16_t Swap16(uint16_t n);
uint32_t Swap32(uint32_t n);
uint64_t Swap64(uint64_t n);

// Mach header

void SwapMachHeader32(MachHeader32 &header);
void SwapMachHeader64(MachHeader64 &header);

// Fat header

void SwapFatHeader(FatHeader &header);
void SwapFatArch(FatArch &arch);