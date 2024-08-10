#pragma once

#include <stdint.h>

// Mach header

#define MH_MAGIC 0xFEEDFACE
#define MH_CIGAM 0xCEFAEDFE

#define MH_MAGIC_64 0xFEEDFACF
#define MH_CIGAM_64 0xCFFAEDFE

#define IS_MACH_MAGIC(magic) (magic == MH_MAGIC || magic == MH_MAGIC_64 || magic == MH_CIGAM || magic == MH_CIGAM_64)

struct MachHeader32
{
    uint32_t magic;
    int32_t cputype;
    int32_t cpusubtype;
    uint32_t filetype;
    uint32_t ncmds;
    uint32_t sizeofcmds;
    uint32_t flags;
};

struct MachHeader64
{
    uint32_t magic;
    int32_t cputype;
    int32_t cpusubtype;
    uint32_t filetype;
    uint32_t ncmds;
    uint32_t sizeofcmds;
    uint32_t flags;
    uint32_t reserved;
};

// FAT header

#define FAT_MAGIC 0xCAFEBABE
#define FAT_CIGAM 0xBEBAFECA

#define IS_FAT_MAGIC(magic) (magic == FAT_MAGIC || magic == FAT_CIGAM)

struct FatHeader
{
    uint32_t magic;
    uint32_t narchs;
};

struct FatArch
{
    uint32_t cputype;
	uint32_t cpusubtype;
	uint32_t offset;
	uint32_t size;
	uint32_t align;
};

// CPU types

#define CPU_ARCH_ABI64 0x01000000

#define CPU_TYPE_X86 7
#define CPU_TYPE_X64 (CPU_TYPE_X86 | CPU_ARCH_ABI64)

#define CPU_TYPE_ARM 12
#define CPU_TYPE_ARM64 (CPU_TYPE_ARM | CPU_ARCH_ABI64)

// Load commands

#define LC_REQ_DYLD 0x80000000

#define	LC_SEGMENT	0x1
#define	LC_SYMTAB	0x2
#define	LC_SYMSEG	0x3
#define	LC_THREAD	0x4
#define	LC_UNIXTHREAD	0x5
#define	LC_LOADFVMLIB	0x6
#define	LC_IDFVMLIB	0x7
#define	LC_IDENT	0x8
#define LC_FVMFILE	0x9
#define LC_PREPAGE      0xa
#define	LC_DYSYMTAB	0xb
#define	LC_LOAD_DYLIB	0xc
#define	LC_ID_DYLIB	0xd
#define LC_LOAD_DYLINKER 0xe
#define LC_ID_DYLINKER	0xf
#define	LC_PREBOUND_DYLIB 0x10
#define	LC_ROUTINES	0x11
#define	LC_SUB_FRAMEWORK 0x12
#define	LC_SUB_UMBRELLA 0x13
#define	LC_SUB_CLIENT	0x14
#define	LC_SUB_LIBRARY  0x15
#define	LC_TWOLEVEL_HINTS 0x16
#define	LC_PREBIND_CKSUM  0x17
#define	LC_LOAD_WEAK_DYLIB (0x18 | LC_REQ_DYLD)
#define	LC_SEGMENT_64	0x19
#define	LC_ROUTINES_64	0x1a
#define LC_UUID
#define LC_RPATH       (0x1c | LC_REQ_DYLD)
#define LC_CODE_SIGNATURE 0x1d
#define LC_SEGMENT_SPLIT_INFO 0x1e
#define LC_REEXPORT_DYLIB (0x1f | LC_REQ_DYLD)
#define	LC_LAZY_LOAD_DYLIB 0x20
#define	LC_ENCRYPTION_INFO 0x21
#define	LC_DYLD_INFO 	0x22
#define	LC_DYLD_INFO_ONLY (0x22|LC_REQ_DYLD)
#define	LC_LOAD_UPWARD_DYLIB (0x23 | LC_REQ_DYLD)
#define LC_VERSION_MIN_MACOSX 0x24
#define LC_VERSION_MIN_IPHONEOS 0x25
#define LC_FUNCTION_STARTS 0x26
#define LC_DYLD_ENVIRONMENT 0x27
#define LC_MAIN (0x28 | LC_REQ_DYLD)
#define LC_DATA_IN_CODE 0x29
#define LC_SOURCE_VERSION 0x2a
#define LC_DYLIB_CODE_SIGN_DRS 0x2b

struct LoadCommand
{
    uint32_t cmd;
    uint32_t size;
};

struct SegmentCommand32
{
    uint32_t cmd;
    uint32_t cmdsize;
    char segname[16];
    uint32_t vmaddr;
    uint32_t vmsize;
    uint32_t fileoff;
    uint32_t filesize;
    int32_t	maxprot;
    int32_t	initprot;
    uint32_t nsects;
    uint32_t flags;
};

struct SegmentCommand64
{
    uint32_t cmd;
    uint32_t cmdsize;
    char segname[16];
    uint64_t vmaddr;
    uint64_t vmsize;
    uint64_t fileoff;
    uint64_t filesize;
    int32_t	maxprot;
    int32_t	initprot;
    uint32_t nsects;
    uint32_t flags;
};

struct Section32
{
    char sectname[16];
    char segname[16];
    uint32_t addr;
    uint32_t size;
    uint32_t offset;
    uint32_t align;
    uint32_t reloff;
    uint32_t nreloc;
    uint32_t flags;
    uint32_t reserved1;
    uint32_t reserved2;
};

struct Section64
{
    char sectname[16];
    char segname[16];
    uint64_t addr;
    uint64_t size;
    uint32_t offset;
    uint32_t align;
    uint32_t reloff;
    uint32_t nreloc;
    uint32_t flags;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
};