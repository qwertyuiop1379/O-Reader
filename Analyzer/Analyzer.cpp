#include "Analyzer.hpp"

#include <Mach-O/Mach-O.hpp>
#include <Reader/Reader.hpp>
#include <Swap/Swap.hpp>

#include <cstdlib>

bool Analyzer::AnalyzeFile(const char *file, std::vector<Analysis> &analyses, std::string *error)
{
    analyses.clear();

    Reader *reader = new Reader();

    if (!reader->OpenFile(file))
    {
        if (error)
            *error = "Failed to open file.";
        return false;
    }
    
    uint32_t magic = reader->Read32(0);
    
    bool isMachMagic = IS_MACH_MAGIC(magic);
    bool isFatMagic = IS_FAT_MAGIC(magic);

    if (!isMachMagic && !isFatMagic)
    {
        if (error)
            *error = "Input is not a mach-o file.";
        return false;
    }

    Analyzer *analyzer = new Analyzer(reader);
    bool success = analyzer->PerformAnalysis(analyses, error);
    delete analyzer;

    return success;
}

bool Analyzer::PerformAnalysis(std::vector<Analysis> &analyses, std::string *error)
{
    uint32_t magic = reader->Read32(0);
    bool isMachMagic = IS_MACH_MAGIC(magic);

    if (isMachMagic)
    {
        Analysis analysis;

        if (!this->AnalyzeMachObject(0, analysis, error))
            return false;

        analyses.push_back(analysis);
    }
    else
    {
        FatHeader fatHeader;
        reader->Read(&fatHeader, 0);

        bool swap = magic == FAT_CIGAM;

        if (swap)
            SwapFatHeader(fatHeader);

        FatArch *archs = static_cast<FatArch *>(malloc(sizeof(FatArch) * fatHeader.narchs));
        reader->Read(archs, sizeof(FatHeader), fatHeader.narchs);

        for (uint32_t i = 0; i < fatHeader.narchs; i++)
        {
            FatArch &arch = archs[i];

            if (swap)
                SwapFatArch(arch);

            Analysis analysis;

            if (!this->AnalyzeMachObject(arch.offset, analysis, error))
                return false;

            analyses.push_back(analysis);
        }

        free(archs);
    }

    return true;
}

bool Analyzer::AnalyzeMachObject(uint64_t offset, Analysis &analysis, std::string *error)
{
    MachHeader32 header;
    this->reader->Read(&header, offset);

    bool swap = header.magic == MH_CIGAM || header.magic == MH_CIGAM_64;

    if (swap)
        SwapMachHeader32(header);

    analysis.architecture = DetermineArchitecture(header.cputype);

    uint64_t commandOffset = offset + (header.magic == MH_MAGIC_64 ? sizeof(MachHeader64) : sizeof(MachHeader32));

    for (uint32_t i = 0; i < header.ncmds; i++)
    {
        if (!this->ProcessLoadCommand(commandOffset, swap, analysis, error))
            return false;
    }

    return true;
}

bool Analyzer::ProcessLoadCommand(uint64_t &commandOffset, bool swap, Analysis &analysis, std::string *error)
{
    LoadCommand loadCommand;
    this->reader->Read(&loadCommand, commandOffset);

    uint32_t size = swap ? Swap32(loadCommand.size) : loadCommand.size;

    if (loadCommand.size == 0)
    {
        if (error)
            *error = "Load command size must be greater than 0.";
        return false;
    }

    commandOffset += size;

    printf("Load command: 0x%x | Size: 0x%x\n", loadCommand.cmd, loadCommand.size);

    return true;
}