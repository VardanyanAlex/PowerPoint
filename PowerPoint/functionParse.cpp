
#include "calcExpr.hpp"
#include "functionParse.hpp"
#include "mainParsing.hpp"
#include "typecheckers.hpp"
#include "variablesInitParse.hpp"

bool isArgument(const SToken& sCurrentToken, const STokenFunc& sTokenFunction, const SymbolTable& aSymbolTable)
{
    if (!sTokenFunction.aFuncArgNames.empty())
    {
        return std::find(sTokenFunction.aFuncArgNames.begin(), sTokenFunction.aFuncArgNames.end(),
            aSymbolTable.GetVariableName(sCurrentToken.TokenIdentifierIdx)) != sTokenFunction.aFuncArgNames.end();
    }
    return false;
}

size_t GetArgIndex(const SToken& sCurrentToken, const STokenFunc& sTokenFunction, const SymbolTable& aSymbolTable)
{
    return std::distance(sTokenFunction.aFuncArgNames.begin(), std::find(sTokenFunction.aFuncArgNames.begin(), sTokenFunction.aFuncArgNames.end(),
        aSymbolTable.GetVariableName(sCurrentToken.TokenIdentifierIdx)));
}

namespace
{
    Tree ParseExprPlusMinus(std::istream& InputStream, STokenFunc& sTokenFunction, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken);

    Tree ParseExprPrimitive(std::istream& InputStream, STokenFunc& sTokenFunction, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken)
    {
        Tree pLeaf = nullptr;
        /*if (sCurrentToken.eType == ETokenType::IdentifierType || sCurrentToken.eType == ETokenType::NumberType)
        {
            pLeaf = CreateTree(sCurrentToken);
            sCurrentToken = nextToken(InputStream, aSymbolTable);
        }*/
        std::string LastIdtfTokenName = aSymbolTable.VariableNameBack();
        if (sCurrentToken.eType == ETokenType::IdentifierType)
        {
            //SToken NextToken = nextToken(InputStream, aSymbolTable);
            //if (NextToken.eType == ETokenType::OperatorType && GetPrecedence(NextToken.TokenOperator) == EOperator::LeftBracket)
            //{
            //    NextToken = nextToken(InputStream, aSymbolTable);
            //    if (NextToken.eType == ETokenType::OperatorType && GetPrecedence(NextToken.TokenOperator) == EOperator::RightBracket)
            //    {
            //        std::string sFuncName = aSymbolTable.GetVariableName(sCurrentToken.TokenIdentifierIdx);
            //        /*if (pFunctionTrees.find(sFuncName) == pFunctionTrees.end())
            //        {
            //            throw CSegFault{};
            //        }*/
            //        /*;
            //        if (pFunctionTrees.find(sFuncName) != pFunctionTrees.end())
            //        {
            //            int iResult{};
            //            EvaluateTree(pFunctionTrees[sFuncName], aVariables, iResult);
            //        }*/
            //    }
            //}
            if (isArgument(sCurrentToken, sTokenFunction, aSymbolTable))
            {
                sCurrentToken.eType = ETokenType::FunctionArgType;
                sCurrentToken.TokenIdentifierIdx = GetArgIndex(sCurrentToken, sTokenFunction, aSymbolTable);

                aSymbolTable.PopVariableName();

                SToken sNode(ETokenType::FunctionArgType, sCurrentToken.TokenIdentifierIdx);
                pLeaf = CreateTree(sNode);
            }
            else if (aSymbolTable.isDefinedVariable(LastIdtfTokenName))
            {
                sCurrentToken.TokenIdentifierIdx = aSymbolTable.GetVariableIdtfIdx(LastIdtfTokenName);
                aSymbolTable.PopVariableName();

                SToken sNode(ETokenType::IdentifierType, sCurrentToken.TokenIdentifierIdx);
                pLeaf = CreateTree(sNode);
            }
            else if (aSymbolTable.isDeclaredFunction(LastIdtfTokenName))
            {
                
                size_t FuncIdx = sCurrentToken.TokenIdentifierIdx = aSymbolTable.GetFunctionIdtfIdx(LastIdtfTokenName);
                aSymbolTable.PopVariableName();

                if (!aSymbolTable.isDefinedFunction(FuncIdx))
                {
                    throw CUndefinedFunction{};
                }

                sCurrentToken = nextToken(InputStream, aSymbolTable);
                if (GetPrecedence(sCurrentToken.TokenOperator) == EOperator::LeftBracket)
                {
                    sCurrentToken = nextToken(InputStream, aSymbolTable);
                    int i = 0;
                    for (i; i < aSymbolTable.GetFunctionArgsCount(FuncIdx) && GetPrecedence(sCurrentToken.TokenOperator) != EOperator::RightBracket; ++i)
                    {
                        Tree arg = ParseExprPlusMinus(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
                        // get argvalues then pass inplace of {}
                        int iArgValue = EvaluateTree(arg, {}, aFunctions, aVariables);
                        
                        sTokenFunction.aFuncArgs.push_back(iArgValue);
                        if (sCurrentToken.eType == ETokenType::EndOfExprType)
                        {
                            sCurrentToken = nextToken(InputStream, aSymbolTable);
                        }
                        else if (GetPrecedence(sCurrentToken.TokenOperator) != EOperator::RightBracket)
                        {
                            throw CUnrecogonized{};
                        }
                    }
                    sTokenFunction.FuncIdentifierIdx = FuncIdx;
                    if (i != aSymbolTable.GetFunctionArgsCount(FuncIdx))
                    {
                        throw CArgsExpectedException{};
                    }
                }
                SToken sNode(ETokenType::FunctionType);
                sNode.TokenFunction = sTokenFunction;
                pLeaf = CreateTree(sNode);
            }
            //else if (IsDefinedFunction(sCurrentToken, aSymbolTable))
            //{
            //    sCurrentToken.TokenIdentifierIdx = aSymbolTable.GetFunctionIdtfIdx(aSymbolTable.VariableNameBack());
            //    aSymbolTable.PopFunctionName();

            //    SToken sNode(ETokenType::IdentifierType, sCurrentToken.TokenIdentifierIdx);
            //    pLeaf = CreateTree(sNode);
            //}
            else
            {
                CSegFault e;
                throw e;
            }
            //sCurrentToken = NextToken;
            sCurrentToken = nextToken(InputStream, aSymbolTable);
        }
        else if (sCurrentToken.eType == ETokenType::NumberType)
        {
            pLeaf = CreateTree(sCurrentToken);
            sCurrentToken = nextToken(InputStream, aSymbolTable);
        }
        return pLeaf;
    }


    Tree ParseExprBracket(std::istream& InputStream, STokenFunc& sTokenFunction, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken)
    {
        Tree pLeaf = nullptr;
        if (GetPrecedence(sCurrentToken.TokenOperator) == EOperator::LeftBracket)
        {
            sCurrentToken = nextToken(InputStream, aSymbolTable);
            pLeaf = ParseExprPlusMinus(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
            // here sCurrentToken must have new created and unscanned token 

            CBracketException e;
            if (GetPrecedence(sCurrentToken.TokenOperator) != EOperator::RightBracket)
            {
                throw e;
            }

            sCurrentToken = nextToken(InputStream, aSymbolTable);
        }
        else if (sCurrentToken.eType == ETokenType::EndOfStatementType || sCurrentToken.eType == ETokenType::EndOfExprType)
        {
            return pLeaf;
        }
        else
        {
            pLeaf = ParseExprPrimitive(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
            // here sCurrentToken must have new created and unscanned token 

        }
        return pLeaf;
    }


    Tree ParseExprMulDiv(std::istream& InputStream, STokenFunc& sTokenFunction, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken)
    {
        Tree pCurrTree = ParseExprBracket(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
        // here sCurrentToken must have new created and unscanned token 

        while (GetPrecedence(sCurrentToken.TokenOperator) & (EOperator::Divide | EOperator::Multiply) )
        {
            SToken sRootOp = sCurrentToken;
            sCurrentToken = nextToken(InputStream, aSymbolTable);
            Tree pRightTree = ParseExprBracket(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
            // here sCurrentToken must have new created and unscanned token 
            pCurrTree = CreateTree(sRootOp, std::move(pCurrTree), std::move(pRightTree));
        }

        return std::move(pCurrTree);
    }



    Tree ParseExprPlusMinus(std::istream& InputStream, STokenFunc& sTokenFunction, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken)
    {
        Tree pCurrTree = ParseExprMulDiv(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
        // here sCurrentToken must have new created and unscanned token 

        while (GetPrecedence(sCurrentToken.TokenOperator) & ( EOperator::Plus | EOperator::Minus))
        {
            SToken sRootOp = sCurrentToken;
            sCurrentToken = nextToken(InputStream, aSymbolTable);
            Tree pRightTree = ParseExprMulDiv(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
            // here sCurrentToken must have new created and unscanned token 
            pCurrTree = CreateTree(sRootOp, std::move(pCurrTree), std::move(pRightTree));
        }
        return std::move(pCurrTree);
    }
}

Tree ParseExprAssignment(std::istream& InputStream, STokenFunc& sTokenFunction, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken)
{
    Tree pCurrTree = ParseExprPlusMinus(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
    // here sCurrentToken must have new created and unscanned token 

    if (sCurrentToken.eType != ETokenType::EndOfStatementType)
    {
        throw CEndOfExprDetection{};
    }

    return std::move(pCurrTree);
}

namespace FunctionParseWork
{
    void ParseArgs(std::istream& InputStream, SymbolTable& aSymbolTable, STokenFunc& sTokenFunction, SToken& sCurrentToken)
    {
        sCurrentToken = nextToken(InputStream, aSymbolTable);

        if (GetPrecedence(sCurrentToken.TokenOperator) != EOperator::LeftBracket)
        {
            throw CBracketException{};
        }

        //pCurrentFunction = std::unique_ptr<SFunctionStructure>(new SFunctionStructure);

        sCurrentToken = nextToken(InputStream, aSymbolTable);
        while (GetPrecedence(sCurrentToken.TokenOperator) != EOperator::RightBracket)
        {
            if (sCurrentToken.eType == ETokenType::IdentifierType)
            {
                //sCurrentToken.eType = ETokenType::FunctionArgType;
                //sCurrentToken.TokenIdentifierIdx = pCurrentFunction->aFuncArgNames.size();
                //pCurrentFunction->aFuncArgNames.push_back(aSymbolTable.VariableNameBack());
                sTokenFunction.aFuncArgNames.push_back(aSymbolTable.VariableNameBack());
                aSymbolTable.PopVariableName();
                sCurrentToken = nextToken(InputStream, aSymbolTable);
            }
            else if (sCurrentToken.eType == ETokenType::EndOfExprType)
            {
                sCurrentToken = nextToken(InputStream, aSymbolTable);
                if (GetPrecedence(sCurrentToken.TokenOperator) == EOperator::RightBracket)
                {
                    throw CIdentifierExpectationException{};
                }
            }
            else
            {
                throw CUnrecogonized{};
            }
        }
    }

    void ParseBody(std::istream& InputStream, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, STokenFunc& sTokenFunction, Tree& pExprTree, SToken& sCurrentToken)
    {
        sCurrentToken = nextToken(InputStream, aSymbolTable);

        if (sCurrentToken.eType == ETokenType::OperatorType && GetPrecedence(sCurrentToken.TokenOperator) == EOperator::Assign)
        {
            sCurrentToken = nextToken(InputStream, aSymbolTable);
            pExprTree = ParseExprAssignment(InputStream, sTokenFunction, aFunctions, aVariables, aSymbolTable, sCurrentToken);
        }
        else if (sCurrentToken.eType == ETokenType::EndOfStatementType)
        {
            pExprTree = nullptr;
        }
        else
        {
            throw CUnrecogonized{};
        }
    }

} // namespace FunctionParseWork

void ParseFunction (std::istream& InputStream, FunctionsData& aFunctions, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken)
{
    sCurrentToken = nextToken(InputStream, aSymbolTable);

    if (sCurrentToken.eType != ETokenType::IdentifierType)
    {
        throw CUnrecogonized{};
    }
    
    Tree pCurrentFunction = nullptr;

    std::string sFuncName = aSymbolTable.VariableNameBack();
    int iFuncIdx = -1;
    if (aSymbolTable.isDeclaredFunction(sFuncName))
    {
        iFuncIdx = aSymbolTable.GetFunctionIdtfIdx(sFuncName);
        // aSymbolTable.PopFunctionName();
        if (aSymbolTable.isDefinedFunction(iFuncIdx))
        {
            throw CODRViolated{};
        }
    }
    aSymbolTable.PopVariableName();
    STokenFunc sCurrentFuncToken;
    pCurrentFunction = Tree(new STree);

    FunctionParseWork::ParseArgs(InputStream, aSymbolTable, sCurrentFuncToken, sCurrentToken);
    
    FunctionParseWork::ParseBody(InputStream, aFunctions, aVariables, aSymbolTable, sCurrentFuncToken, pCurrentFunction,  sCurrentToken);
    if (iFuncIdx == -1) // if true,  this function is declared and defined at this moment 
    {
        aFunctions.push_back(std::move(pCurrentFunction));
        iFuncIdx = aFunctions.size() - 1;
    }
    else
    {
        aFunctions[iFuncIdx] = std::move(pCurrentFunction);
    }

    aSymbolTable.InsertFunctionInfo(std::move(sFuncName), sCurrentFuncToken.aFuncArgNames.size(), aFunctions[iFuncIdx] != nullptr);
}
