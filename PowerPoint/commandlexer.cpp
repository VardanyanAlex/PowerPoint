
#include <iostream>

#include "commandlexer.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{
//////////////////////////////////////////////////////////////////////
// CLexer class impl
//////////////////////////////////////////////////////////////////////
std::string CLexer::NextLexemme(std::istream& sInput) const
{
    SkipSpaces(sInput);
    char cLexemmeChar{};
    std::string sLexemme = "";
    if (sInput.eof())
    {
        return sLexemme;
    }

    if (isalpha(sInput.peek()))
    {
        while (isalpha(sInput.peek()))
        {
            sInput.get(cLexemmeChar);
            sLexemme += cLexemmeChar;
        }
    }
    else if (isdigit(sInput.peek()))
    {
        while (isdigit(sInput.peek()))
        {
            sInput.get(cLexemmeChar);
            sLexemme += cLexemmeChar;
        }
    }
    else if (ispunct(sInput.peek()))
    {
        sInput.get(cLexemmeChar);
        sLexemme += cLexemmeChar;
        if (ispunct(sInput.peek()))
        {
            sInput.get(cLexemmeChar);
            sLexemme += cLexemmeChar;
            while (isalpha(sInput.peek()))
            {
                sInput.get(cLexemmeChar);
                sLexemme += cLexemmeChar;
            }
        }
    }
    else
    {
        //throw CLexerException{};
    }

    return sLexemme;
}

void CLexer::SkipSpaces(std::istream& sInput) const
{
    while (sInput.peek() == ' ' || sInput.peek() == '\n' || sInput.peek() == '#')
    {
        if (sInput.peek() == '#')
            sInput.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        else
            sInput.get();
    }
}
//////////////////////////////////////////////////////////////////////

} // namespace Command
//////////////////////////////////////////////////////////////////////
} // namespace pwpt
