
#ifndef _POWERPOINT_COMMAND_TOKEN_HPP_
#define _POWERPOINT_COMMAND_TOKEN_HPP_

#include <map>
#include <string>

namespace pwpt
{
//////////////////////////////////////////////////////////////
namespace Command
{
//////////////////////////////////////////////////////////////
enum ETokenType
{
	Invalid,

	Command,
	Option,
	OptionValue,
	Punct
};

enum class EOperation
{
	Invalid,

	// toolbar related commands
	Set,
	Reset,
	// slideshow modification related commands
	AddSlide,
	Clear,
	Draw,
	Remove,
	Move,
	Copy,
	// Persistence related commands
	Save,
	Load,
	// informational commands
	Print,

	Help
};

enum class EOption
{
	Invalid,

	Shape,
	Color,
	Size,
	All,

	Object,

	Slide,

	From,
	To
};

enum class EPunct
{
	Invalid,

	Dash,		// '-'
	Comma		// ','
};

struct SOptionValue
{
	SOptionValue() = default;
	SOptionValue(std::string const& sValue);
	explicit SOptionValue(unsigned const nValue);

	bool IsValueNumber() const;
	bool IsValueText() const;

	void SetNumber(int);
	void SetText(std::string const&);

	bool IsValid() const;

	int			iNumberValue = -1;
	std::string sTextValue = "";
};
using OptionValueMap = std::map<EOption, SOptionValue>;

//////////////////////////////////////////////////////////////
// SToken struct
//////////////////////////////////////////////////////////////
struct SToken
{
	ETokenType eType = ETokenType::Invalid;

	union
	{
		EOperation	eOperation;
		EOption		eOption;
		EPunct		ePunct; // e.g. ','  in coordinates representation
		// . . .
	};
	SOptionValue oValue;
};
//////////////////////////////////////////////////////////////
} // namespace Command
//////////////////////////////////////////////////////////////
} // namespace pwpt

#endif // _POWERPOINT_COMMAND_TOKEN_HPP_
