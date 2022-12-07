

#include "calcExpr.hpp"
#include "functionParse.hpp"
#include "lexer.hpp"
#include "mainParsing.hpp"
#include "variablesInitParse.hpp"

#include <iterator>

namespace
{
    void ParseProgram(FunctionsData& aFunctions, VariablesData& aVariables, std::istream& Input, SymbolTable& aSymbolTable)
    {
        while (!Input.eof())
        {
            SToken sCurrentToken = nextToken(Input, aSymbolTable);
            SFunction pCurrentFunc{};

            if (sCurrentToken.eType == ETokenType::KeywordType)
            {
                switch (sCurrentToken.TokenKeyword)
                {
                case EKeywordType::func:
                    ParseFunction(Input, aFunctions, aVariables, aSymbolTable, sCurrentToken);
                    break;
                case EKeywordType::var:
                    ParseVarInit(aVariables, aFunctions, Input, aSymbolTable);
                    break;
                default:
                    throw CUnrecogonized{};
                    break;
                }
            }
            else if(sCurrentToken.eType != ETokenType::EndOfStatementType)
            {
                throw CUnrecogonized{};
            }
            SkipSpaces(Input);
        }
    }
}  // unnamed namespace

void Parser(FunctionsData& pFunctionTrees, VariablesData& aVariables, std::istream& Input, SymbolTable& aSymbolTable)
{
    ParseProgram(pFunctionTrees, aVariables, Input, aSymbolTable);
}
