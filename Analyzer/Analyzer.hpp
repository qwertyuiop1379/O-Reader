#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include <Analyzer/Architecture.hpp>

struct Analysis
{
    Architecture architecture;
};

class Reader;

struct mach_header;

class Analyzer
{
    private:
        Reader *reader;

        Analyzer(Reader *reader)
            : reader(reader) { }
            
        bool PerformAnalysis(std::vector<Analysis> &analyses, std::string *error);
        bool AnalyzeMachObject(uint64_t offset, Analysis &analysis, std::string *error);

        bool ProcessLoadCommand(uint64_t &commandOffset, bool swap, Analysis &analysis, std::string *error);

    public:
        static bool AnalyzeFile(const char *file, std::vector<Analysis> &analyses, std::string *error);
};
