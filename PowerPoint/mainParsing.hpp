
#ifndef MAINPARSING_HPP
#define MAINPARSING_HPP

#include <exception>
#include <string>
#include <vector>

#include "tree.hpp"
#include "typecheckers.hpp"
#include "SymbolTable.hpp"

void Parser(FunctionsData&, VariablesData&, std::istream& Input, SymbolTable&);

class CODRViolated : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: one-definition-rule was violated \n";
    }
};

class CArgsExpectedException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: more arguments expected \n";
    }
};

class CBracketException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: bracket expected\n";
    } 
};

class CIdentifierExpectationException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: identifier expected\n";
    }
};

class CLValueException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: left side must be lValue\n";
    }
};

class CAssignExpectedException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: assignment operator expected \n";
    }
};

class CRValueException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: initializer must be identifier or number type\n";
    }
};

class CUnrecogonized : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: Unrecogonized token detected \n";
    }
};

class CUnexpected : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tException thrown: Unexpected token detected \n";
    }
};

class CSegFault : public std::exception
{
public:

    const char* what() const throw() override
    {
        return (("Exception thrown: Undefined identifier detected \n" ) );
    }
};


#endif // MAINPARSING_HPP
