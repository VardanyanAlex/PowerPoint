
#ifndef _POWERPOINT_PARSER_HPP
#define _POWERPOINT_PARSER_HPP

#include <string>

class CParser
{
public:
	void Parse(std::stringstream const& sInput);

private:
	CTokenizer	m_oTokenizer;
	CLexer		m_oLexer;
};

#endif // _POWERPOINT_PARSER_HPP
