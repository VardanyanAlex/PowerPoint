
#include <string>
#include <iostream>

#include "SymbolTable.hpp"
#include "typecheckers.hpp"


bool IsDefinedVariable(SToken& sToken, SymbolTable& aSymbolTable)
{
    return sToken.TokenIdentifierIdx <= (aSymbolTable.VariablesNamesCount() - 1);
}

bool IsDefinedFunction(SToken& sToken, SymbolTable& aSymbolTable)
{
    return sToken.TokenIdentifierIdx <= (aSymbolTable.FunctionNamesCount() - 1);
}

bool IsOperator(char cOperator)
{
    switch(cOperator)
    {
        case '+':
        case '-':
        case '/':
        case '*':
        case '(':
        case ')':
        case '=':
            return true;
            break;
    }
    return false;
}

bool IsIdentifier(std::string& sLexemme)
{
    if( (sLexemme[0] >= 'a' && sLexemme[0] <= 'z') || (sLexemme[0] >= 'A' && sLexemme[0] <= 'Z'))
    {
        for (size_t i = 1; i < sLexemme.length(); ++i)
        {
            try
            {
                CTokenizeException e;
                if(isalpha(sLexemme[i]) == 0 && isdigit(sLexemme[i]) == 0)
                {
                    throw e;
                }

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                exit(1);
            }

        }
        return true;
    }
    return false;
}


bool IsNumber(std::string& sNumber)
{

    if(sNumber[0] >= '0' && sNumber[0] <= '9')
    {
        for(size_t i = 1; i < sNumber.length(); ++i)
        {
            
            try
            {
                CTokenizeException e;
                if(sNumber[i] < '0' || sNumber[i] > '9')
                {
                    throw e;
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                exit(1);
            }
            
        }
        return true;
    }
    return false;
    
}

bool IsEndOfStatement(char cOp)
{
    return (cOp == ';') ? true : false;
}

bool IsEndOfExpr(char cOp)
{
    return (cOp == ',') ? true : false;
}

bool IsKeyword(std::string sWord)
{
    return (std::find(aKeywords.begin(), aKeywords.end(), sWord) != aKeywords.end()) ? true : false;
    
}


EOperator GetPrecedence(char cOp)
{
    switch(cOp)
    {
        case '=':
            return EOperator::Assign;
        break;    
        case '+':
            return EOperator::Plus;
        break;
        case '-':
            return EOperator::Minus;
        break;
        case '/':
            return EOperator::Divide;
        break;
        case '*':
            return EOperator::Multiply;
        break;
        case '(':
            return EOperator::LeftBracket;
        break;
        case ')':
            return EOperator::RightBracket;
        break;
        default:
        break;
    }
    return EOperator::OUnknown;
}

