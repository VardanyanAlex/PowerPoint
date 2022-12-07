
#include <fstream>
#include <sstream>

#include <iostream>

#include "codeGeneration.hpp"
#include "getConsoleArguments.hpp"
#include "interpreterRequirments.hpp"
#include "mainParsing.hpp"
#include "SymbolTable.hpp"


void Compile(int argc, char** argv)
{
    try
    {
        std::unique_ptr<std::istream> InputStream = nullptr;
        std::unique_ptr<std::ostream> OutputStream = nullptr;

        GetConsoleArguments(argc, &argv[0], OutputStream, InputStream);

        SymbolTable aSymbolTable;

        VariablesData aData;
        FunctionsData aFunctions;

        Parser(aFunctions, aData, *InputStream, aSymbolTable);

        SCode sCodeSegment;

        CodeGenerator(aFunctions, aData, sCodeSegment, *OutputStream, aSymbolTable);

        Memory RAM{ nullptr };
        Registers aRegisters;

        CInterpreter  cInterpreter;
        Load(RAM, sCodeSegment, aData, cInterpreter);

        cInterpreter.Work(aRegisters, RAM, aSymbolTable);

        delete[] RAM;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }
    catch (...)
    {
        std::cerr << "Unknown Exception thrown !!! " << std::endl;
    }
}

int main(int argc, char** argv)
{
    Compile(argc, argv);

    return 0;
}
