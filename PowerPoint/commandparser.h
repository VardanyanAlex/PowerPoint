
#ifndef _POWERPOINT_PARSER_HPP
#define _POWERPOINT_PARSER_HPP

#include <string>

#include "pwpt_icommand.h"

namespace pwpt
{

namespace Command
{

class CParser
{
public:
	pwpt::ICommandsList Parse(std::stringstream const& sInput);

private:
	CTokenizer	m_oTokenizer;
	CLexer		m_oLexer;
};

} // namespace Command

} // namespace pwpt

#endif // _POWERPOINT_PARSER_HPP
