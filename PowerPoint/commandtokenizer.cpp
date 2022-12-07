
#include "commandtokenizer.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{

//////////////////////////////////////////////////////////////////////
// CTokenizer class impl
//////////////////////////////////////////////////////////////////////
CTokenizer::CTokenizer()
{
    //PrepareTranslates();
}

SToken CTokenizer::NextToken(std::istream& sInput)
{
    std::string sLexemme = m_oLexer.NextLexemme(sInput);
    
    SToken sToken;
    if (IsPunct(sLexemme))
    {
        sToken.eType = ETokenType::Punct;
        sToken.cPunct = sLexemme[0];
    }
    else if (IsNumber(sLexemme))
    {
        sToken.eType = ETokenType::Number;
        sToken.iNumber = std::stoi(sLexemme);
    }
    else if (IsWord(sLexemme))
    {
        sToken.eType = ETokenType::Word;
        sToken.sWord = sLexemme;
    }
    else if (sLexemme == "")
    {
        /*CEndOfExprDetection e;
        throw e;*/
    }

    return sToken;
}

bool CTokenizer::IsPunct(std::string const& sLexemme) const
{
    return sLexemme.size() == 1 && ispunct(sLexemme[0]);
}

bool CTokenizer::IsNumber(std::string const& sLexemme) const
{
    bool bIsNumber = true;

    if (sLexemme[0] < '1' || sLexemme[0] > '9')
        return false;

    for (auto const& c : sLexemme)
    {
        if (!std::isdigit(c))
        {
            bIsNumber = false;
            break;
        }
    }
    
    return bIsNumber;
}

bool CTokenizer::IsWord(std::string const& sLexemme) const
{
    bool bIsWord = true;

    for (auto const& c : sLexemme)
    {
        if (!isalpha(c) && c != '-')
        {
            bIsWord = false;
            break;
        }
    }

    return bIsWord;
}

//void CTokenizer::PrepareTranslates()
//{
//    m_oOperationTranslater = 
//    {
//        {"set",		EOperation::Set},
//        {"reset",	EOperation::Reset},
//        {"add",     EOperation::Add},
//        {"clear",	EOperation::Clear},
//        {"draw",	EOperation::Draw},
//        {"remove",	EOperation::Remove},
//        {"move",	EOperation::Move},
//        {"copy",	EOperation::Copy},
//        {"save",	EOperation::Save},
//        {"load",	EOperation::Load},
//        {"print",	EOperation::Print},
//        {"help",	EOperation::Help}
//    };
//
//    m_oOptionTranslater =
//    {
//        {"--shape",   EOption::Shape },
//        {"--color",   EOption::Color },
//        {"--size",    EOption::PencilThickness },
//        {"--all",     EOption::All },
//        {"--object",  EOption::Object },
//        {"--slide",   EOption::Slide },
//        {"--filepath",EOption::Filepath },
//        {"--from",    EOption::From },
//        {"--to",      EOption::To }
//    };
//
//    m_oPunctTranslater =
//    {
//        { ",", EPunct::Comma },
//        { "-", EPunct::Dash },
//        { "[", EPunct::LeftBracket },
//        { "]", EPunct::RightBracket }
//    };
//}

//////////////////////////////////////////////////////////////////////
} // namespace Command
//////////////////////////////////////////////////////////////////////
} // namespace pwpt
