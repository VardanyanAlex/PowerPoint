
#include "calcExpr.hpp"
#include "functionParse.hpp"
#include "mainParsing.hpp"
#include "tokenizer.hpp"

namespace
{
    int Calculate(const int iOperandOne,const int iOperandTwo, const char cOperator)
    {
        switch (GetPrecedence(cOperator))
        {
        case EOperator::Plus:
            return iOperandOne + iOperandTwo;
            break;
        case EOperator::Minus:
            return iOperandOne - iOperandTwo;
            break;
        case EOperator::Multiply:
            return iOperandOne * iOperandTwo;
            break;
        case EOperator::Divide:
            return iOperandOne / iOperandTwo;
            break;
        default:
            break;
        }
    }

    int EvaluateTreeWorker(const Tree& ExpTree, const FunctionArgsValues& FuncArgs, FunctionsData& aFunctions, const VariablesData& aVariables)
    {
        if (ExpTree != nullptr)
        {
            int iLefttOperand = EvaluateTree(ExpTree->pLeft, FuncArgs, aFunctions, aVariables);
            int iRightOperand = EvaluateTree(ExpTree->pRight, FuncArgs, aFunctions, aVariables);

            switch (ExpTree->Value.eType)
            {
            case ETokenType::OperatorType:
            {
                return Calculate(iLefttOperand, iRightOperand, ExpTree->Value.TokenOperator);
                break;
            }
            case ETokenType::NumberType:
                return ExpTree->Value.TokenNumber;
                break;
            case ETokenType::IdentifierType:
                return aVariables[ExpTree->Value.TokenIdentifierIdx];
                break;
            case ETokenType::FunctionArgType:
                return !FuncArgs.empty() ? FuncArgs[ExpTree->Value.TokenIdentifierIdx] : 0;
                break;
            case ETokenType::FunctionType:
            {
                int iRes = EvaluateTree(aFunctions[ExpTree->Value.TokenFunction.FuncIdentifierIdx],
                    ExpTree->Value.TokenFunction.aFuncArgs, aFunctions, aVariables);

                for (; !ExpTree->Value.TokenFunction.aFuncArgs.empty();)
                {
                    ExpTree->Value.TokenFunction.aFuncArgs.pop_back();
                }
                return iRes;
            }
            break;
            default:
                break;
            }
        }
    }
} // unnamed namespace


// Wrapper function
int EvaluateTree(const Tree& ExpTree,  const FunctionArgsValues& FuncArgs, FunctionsData& aFunctions,  const VariablesData& aVariables)
{
    return EvaluateTreeWorker(ExpTree, FuncArgs, aFunctions, aVariables);
}

//void calcConstExpFunc(std::istream& InputStream, SFunction& pCurrentFunction, VariablesData& aVariables, SymbolTable& aSymbolTable, SToken& sCurrentToken)
//{
//    SToken FuncName = nextToken(InputStream, aSymbolTable);
//    Tree pCurrTree = nullptr;
//    if (FuncName.eType != ETokenType::IdentifierType)
//    {
//        CLValueException e;
//        throw e;
//    }
//    else
//    {
//        pCurrTree = CreateTree(FuncName);
//    }
//    SToken TokenOperator = nextToken(InputStream, aSymbolTable);
//
//    if (GetPrecedence(TokenOperator.TokenOperator) == EOperator::Assign)
//    {
//        sCurrentToken = nextToken(InputStream, aSymbolTable);
//        Tree pExpressionTree = ParseExprAssignment(InputStream, pCurrentFunction, aVariables, aSymbolTable, sCurrentToken);
//        int iRValue{};
//        //EvaluateTree(pExpressionTree, aVariables, iRValue);
//        // here sCurrentToken must have new created and unscanned token 
//
//        aVariables.push_back(iRValue);
//    }
//
//    CEndOfExprDetection e;
//    if (sCurrentToken.eType != ETokenType::EndOfStatementType)
//    {
//        throw e;
//    }
//}
