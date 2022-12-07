
#ifndef _POWERPOINT_PARSER_HPP
#define _POWERPOINT_PARSER_HPP

#include <string>

#include "commandtokenizer.h"
#include "pwpt_icommand.h"

namespace pwpt
{

namespace Command
{

class CParser
{
public:
	pwpt::ICommand_SPtr Parse(std::istream& sInput);

private:
	CTokenizer	m_oTokenizer;
};

} // namespace Command

} // namespace pwpt

#endif // _POWERPOINT_PARSER_HPP
