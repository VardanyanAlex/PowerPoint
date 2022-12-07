
#include "calcExpr.hpp"
#include "functionParse.hpp"
#include "mainParsing.hpp"
#include "tokenizer.hpp"


Tree&& ParseVarInit(VariablesData& aVariables, FunctionsData& aFunctions, std::istream& Input, SymbolTable& aSymbolTable)
{
    // variable name
    SToken sLValue = nextToken(Input, aSymbolTable);
    if (sLValue.eType != ETokenType::IdentifierType)
    {
        throw CLValueException{};
    }
    if (aSymbolTable.isDefinedVariable(aSymbolTable.VariableNameBack()))
    {
        throw CODRViolated{};
    }
    ////////////////////////////////////////////////////

    // endOfExpr(;) or assignment operator(=)
    SToken sAssign = nextToken(Input, aSymbolTable);
    if (sAssign.eType == ETokenType::EndOfStatementType)
    {
        aVariables.push_back(int{});
        SToken sNode(ETokenType::NumberType, 0);
        Tree pLeaf = CreateTree(sNode);
        return std::move(pLeaf);
    }
    else if (GetPrecedence(sAssign.TokenOperator) != EOperator::Assign)
    {
        throw CAssignExpectedException{};
    }
    ///////////////////////////////////////////////////////////////////////////////////////////

    SToken sCurrentToken = nextToken(Input, aSymbolTable);
    // Rvalue variable name or number

    STokenFunc temp; // only needed for ParseExprAssignment() function
    Tree pExpressionTree = ParseExprAssignment(Input, temp, aFunctions, aVariables, aSymbolTable, sCurrentToken);
    int iRValue = EvaluateTree(pExpressionTree, temp.aFuncArgs, aFunctions, aVariables);
    temp.aFuncArgs.clear();
    ///////////////////////////////////////////////////////////////////////////////////////////

    aVariables.push_back(iRValue);

    return std::move(pExpressionTree);
}

