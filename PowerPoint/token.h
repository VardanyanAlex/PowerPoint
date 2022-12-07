
#ifndef _POWERPOINT_COMMAND_TOKEN_HPP_
#define _POWERPOINT_COMMAND_TOKEN_HPP_

#include <map>
#include <string>

#include "commandscomponents.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////
namespace Command
{
//////////////////////////////////////////////////////////////
enum class ETokenType
{
	Invalid,

	Number,
	Word,
	Punct
};

enum class EPunct
{
	Invalid,

	Dash,		// '-'
	Comma,		// ','
	LeftBracket,
	RightBracket
};

//////////////////////////////////////////////////////////////
// SToken struct
//////////////////////////////////////////////////////////////
struct SToken
{
	ETokenType eType = ETokenType::Invalid;

	union
	{
		int iNumber;
		char cPunct;
		// . . .
	};
	std::string sWord;
};
//////////////////////////////////////////////////////////////
} // namespace Command
//////////////////////////////////////////////////////////////
} // namespace pwpt

#endif // _POWERPOINT_COMMAND_TOKEN_HPP_
