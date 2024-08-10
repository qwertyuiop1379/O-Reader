#include <cstdio>

#include <Analyzer/Analyzer.hpp>

int main(int argc, char **argv)
{
    std::vector<Analysis> analyses;
    std::string error;

    if (!Analyzer::AnalyzeFile(argv[0], analyses, &error))
    {
        printf("Error: %s\n", error.c_str());
        return 1;
    }

    for (const Analysis &a : analyses)
        printf("Supported architecture: %s\n", StringForArchitecture(a.architecture));

    return 0;
}