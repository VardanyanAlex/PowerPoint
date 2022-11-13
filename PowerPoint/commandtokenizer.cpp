
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
    m_oOperationTranslater = {
        {"set",		EOperation::Set},
        {"reset",	EOperation::Reset},
        {"addSlide",EOperation::AddSlide},
        {"clear",	EOperation::Clear},
        {"draw",	EOperation::Draw},
        {"remove",	EOperation::Remove},
        {"move",	EOperation::Move},
        {"copy",	EOperation::Copy},
        {"save",	EOperation::Save},
        {"load",	EOperation::Load},
        {"print",	EOperation::Print},
        {"help",	EOperation::Help}
    };

    m_oOptionTranslater =
    {
        {"shape",   EOption::Shape },
        {"color",   EOption::Color },
        {"size",    EOption::Size },
        {"all",     EOption::All },
        {"object",  EOption::Object },
        {"slide",   EOption::Slide },
        {"from",    EOption::From },
        {"to",      EOption::To }
    };
}

SToken CTokenizer::NextToken(std::istream& sInput)
{
    std::string sLexemme = m_oLexer.NextLexemme(sInput);
    
    SToken sToken;
    if (IsOperationKeyword(sLexemme))
    {
        sToken.eType = ETokenType::Command;
        sToken.eOperation = m_oOperationTranslater[sLexemme];
    }
    else if (IsOptionKeyword(sLexemme))
    {
        sToken.eType = ETokenType::Option;
        sToken.eOption = m_oOptionTranslater[sLexemme];
    }
    else if (IsPunct(sLexemme))
    {
        sToken.eType = ETokenType::Punct;
        sToken.ePunct = m_oPunctTranslater[sLexemme];
    }
    else if (IsNumberValue(sLexemme))
    {
        sToken.eType = ETokenType::OptionValue;
        //sToken.oValue.SetNumber(stoi(sLexemme));
    }
    else if (IsTextValue(sLexemme))
    {
        sToken.eType = ETokenType::OptionValue;
        //sToken.oValue.SetText(sLexemme);
    }
    else
    {
        if (sLexemme == "")
        {
            /*CEndOfExprDetection e;
            throw e;*/
        }
    }

    return sToken;
}

bool CTokenizer::IsOperationKeyword(std::string const& sLexemme) const
{
    return m_oOperationTranslater.contains(sLexemme);
}

bool CTokenizer::IsOptionKeyword(std::string const& sLexemme) const
{
    return m_oOptionTranslater.contains(sLexemme);
}

bool CTokenizer::IsPunct(std::string const& sLexemme) const
{
    return m_oPunctTranslater.contains(sLexemme);
}

bool CTokenizer::IsNumberValue(std::string const& sLexemme) const
{
    bool bIsNumber = true;

    if (sLexemme[0] < '1' || sLexemme[0] > '9')
        return bIsNumber;

    for (char const& c : sLexemme)
    {
        if (!std::isdigit(c))
        {
            bIsNumber = false;
            break;
        }
    }
    
    return bIsNumber;
}

bool CTokenizer::IsTextValue(std::string const& sLexemme) const
{
    return true;
}
//////////////////////////////////////////////////////////////////////
} // namespace Command
//////////////////////////////////////////////////////////////////////
} // namespace pwpt
