
#ifndef TYPECHECKERS_HPP
#define TYPECHECKERS_HPP

#include <exception>
#include <vector>

#include "tree.hpp"
#include "SymbolTable.hpp"

const std::vector<std::string> aKeywords{ "func", "var", "constexpr", "begin", "end"};

enum EOperator
{
    Assign = 0,
    Plus = 1,
    Minus = 2,
    Divide = 4,
    Multiply = 8,
    LeftBracket = 16,
    RightBracket = 32,
    OUnknown = 128
};

using VariablesData = std::vector<int>;
using NamesTable = std::vector<std::string>;

/*
* brief: returns true if passed SToken is in VariablesData, and false otherwise 
*/
bool IsDefinedVariable(SToken&, SymbolTable&);

/*
* brief: returns true if passed SToken is defined functiom
*/
bool IsDefinedFunction(SToken&, SymbolTable&);

/*
* brief: return true if op is equal to one of 
*        {'*', '/', '+', '-', '(', ')'} characters
*/
bool IsOperator(char op);

/*
* brief: returns true when word is an identifier in expression
*/
bool IsIdentifier(std::string& sLexemme);

/*
* brief: returns true when num is a number in expression
*/
bool IsNumber(std::string& sNumber);

/*
* brief: returns true if lexxeme is ;
*/
bool IsEndOfStatement(char cOp);

/*
* brief: returns true if lexxeme is ,
*/
bool IsEndOfExpr(char cOp);

/*
* brief: returns true if lexemme is keyword
*/
bool IsKeyword(std::string sWord);

/*
* brief: returns precedence of operator
*/
EOperator GetPrecedence(char cOp);

class CTokenizeException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tExcpetion thrown: unrecognized token \n";
    } 
};

#endif // TYPECHECKERS_HPP
