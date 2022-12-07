
#ifndef FUNCTIONPARSE_HPP
#define FUNCTIONPARSE_HPP

#include <deque>

#include "tokenizer.hpp"

struct SFunctionStructure
{
    SFunctionStructure() =default;
    
    Tree pExpTree = nullptr;
    std::vector<std::string> aFuncArgNames{};
    std::deque<int> aFuncArgValues{};
};

using SFunction = std::unique_ptr<SFunctionStructure>;
using FunctionsData = std::vector<Tree>;
using FunctionArgsValues = std::vector<int>;


void ParseFunction(std::istream&, FunctionsData&, VariablesData&, SymbolTable&, SToken&);

Tree ParseExprAssignment(std::istream&, STokenFunc&, FunctionsData&, VariablesData&, SymbolTable&, SToken&);

bool isArgument(const SToken&, const SFunction&, const SymbolTable&);

size_t GetArgIndex(const SToken&, const SFunction&, const SymbolTable&);

class CInValidArgs : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: invalid arguments for function\n";
    }
};

class CUndefinedFunction : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: function is declared, but not defined \n";
    }
};


#endif // FUNCTIONPARSE_HPP