#include "Architecture.hpp"

#include <Mach-O/Mach-O.hpp>

Architecture DetermineArchitecture(int32_t cputype)
{
    switch (cputype)
    {
        case CPU_TYPE_X86: return Architecture::x86;
        case CPU_TYPE_X64: return Architecture::x64;
        case CPU_TYPE_ARM: return Architecture::ARM32;
        case CPU_TYPE_ARM64: return Architecture::ARM64;

        default: return Architecture::Unknown;
    }
}

const char *StringForArchitecture(Architecture a)
{
    switch (a)
    {
        case Architecture::x86: return "x86";
        case Architecture::x64: return "x64";
        case Architecture::ARM32: return "arm";
        case Architecture::ARM64: return "arm64";

        default: return "unknown";
    }
}