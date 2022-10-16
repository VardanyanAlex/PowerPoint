
#ifndef _POWERPOINT_PARSER_HPP
#define _POWERPOINT_PARSER_HPP

#include <string>

#include "pwpt_icommand.h"

class CParser
{
public:
	pwpt::ICommand_Ptr Parse(std::stringstream const& sInput);

private:
	CTokenizer	m_oTokenizer;
	CLexer		m_oLexer;
};

#endif // _POWERPOINT_PARSER_HPP
