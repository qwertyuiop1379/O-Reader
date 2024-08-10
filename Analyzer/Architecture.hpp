#pragma once

#include <cstdint>

enum class Architecture
{
    Unknown,
    x86,
    x64,
    ARM32,
    ARM64,
};

Architecture DetermineArchitecture(int32_t cputype);
const char *StringForArchitecture(Architecture a);