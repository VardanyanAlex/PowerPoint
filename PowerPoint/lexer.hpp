
#ifndef LEXER_HPP
#define LEXER_HPP

#include <exception>
#include <iostream>
#include <string>

void SkipSpaces(std::istream& Input);

/*
* brief: returns one lexem
*/
std::string nextLexemme(std::istream& Input);

class CLexerException : public std::exception
{
public:
    const char* what() const throw() override
    {
        return "\tExcpetion thrown: unrecognized lexemme \n";
    } 
};

#endif // LEXER_HPP
