
#include <iostream>
#include <limits>
#include <string>

#include "lexer.hpp"


void SkipSpaces(std::istream& Input)
{
    while(Input.peek() == ' ' || Input.peek() == '\n' || Input.peek() == '#')
    {
        if (Input.peek() == '#')
        {
            Input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            Input.get();
        }
    }
}

std::string nextLexemme(std::istream& Input)
{
    SkipSpaces(Input);
    char cLexemmeChar{};
    std::string sLexemme = "";
    if(Input.eof())
    {
        return "";
    }
    if(isalpha(Input.peek()))
    {
        while(isalpha(Input.peek()) || isdigit(Input.peek()))
        {
            Input.get(cLexemmeChar);
            sLexemme += cLexemmeChar;
        }
    }
    else if(isdigit(Input.peek()))
    {
        while(isdigit(Input.peek()))
        {
            Input.get(cLexemmeChar);
            sLexemme += cLexemmeChar;
        }
    }
    else if(ispunct(Input.peek()))
    {
        Input.get(cLexemmeChar);
        sLexemme += cLexemmeChar;
    }
    else
    {
         throw CLexerException{};
    }
    return sLexemme;
}
