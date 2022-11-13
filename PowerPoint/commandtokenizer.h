
#ifndef _POWERPOINT_COMMAND_TOKENIZER_HPP_
#define _POWERPOINT_COMMAND_TOKENIZER_HPP_

#include <map>
#include <string>

#include "commandlexer.h"
#include "token.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{
//////////////////////////////////////////////////////////////////////
// CTokenizer class
//////////////////////////////////////////////////////////////////////
class CTokenizer
{
public:
	CTokenizer();

	CTokenizer(CTokenizer const&) = delete;
	CTokenizer& operator=(CTokenizer const&) = delete;

	SToken NextToken(std::istream& sInput);

// Helper functions
private:
	bool IsOperationKeyword(std::string const&) const;
	bool IsOptionKeyword(std::string const&) const;
	bool IsPunct(std::string const&) const;
	bool IsNumberValue(std::string const&) const;
	bool IsTextValue(std::string const&) const;

	// Translates gotten lexemme to int for one of EOperation, EOption or EPunct
	//int TranslateToInt(std::string const&, int&) const;

private:
	CLexer m_oLexer{};

	// Do we need separate generic class for translation ???
	std::map<std::string, EOperation>	m_oOperationTranslater;
	std::map<std::string, EOption>		m_oOptionTranslater;
	std::map<std::string, EPunct>		m_oPunctTranslater;
};
//////////////////////////////////////////////////////////////////////
} // namespace Command
//////////////////////////////////////////////////////////////////////
} // namespace pwpt

#endif // _POWERPOINT_COMMAND_TOKENIZER_HPP_
