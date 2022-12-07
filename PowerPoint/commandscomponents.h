
#ifndef _POWERPOINT_COMMAND_COMPONENTS_HPP_
#define _POWERPOINT_COMMAND_COMPONENTS_HPP_

#include <map>

namespace pwpt
{

enum class EOperation
{
	Invalid,

	// toolbar related commands
	Set,
	Reset,
	// slideshow modification related commands
	Add,
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
	PencilThickness,
	All,

	Object,

	Slide,
	Filepath,

	From,
	To
};

struct SOptionValue
{
	SOptionValue() = default;
	SOptionValue(std::string const& sValue);
	explicit SOptionValue(int const nValue);

	bool IsValueNumber() const;
	bool IsValueText() const;

	void SetNumber(int);
	void SetText(std::string const&);

	bool IsValid() const;

	int			m_iNumberValue = -1;
	std::string m_sTextValue = "";
};
using OptionValueMap = std::map<typename EOption, class SOptionValue>;

} // namespace pwpt

#endif // _POWERPOINT_COMMAND_COMPONENTS_HPP_
