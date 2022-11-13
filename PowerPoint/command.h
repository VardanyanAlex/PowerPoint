
#ifndef _POWERPOINT_COMMAND_HPP_
#define _POWERPOINT_COMMAND_HPP_

#include "pwpt_icommand.h"
#include "token.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 
//////////////////////////////////////////////////////////////////////
// CCommand class 
// interface ICommand impl 
//////////////////////////////////////////////////////////////////////
class CCommand : public ICommand
{
public:
	CCommand() =default;

	CCommand(CCommand const&) =delete;
	CCommand& operator=(CCommand const&) =delete;

// ICommand's functions
public:
	EOperation GetCommandType() const override;

	OptionValueMap GetOptions() const override;
	SOptionValue GetValue(EOption) const override;

public:
	void SetCommandType(EOperation const);
	void SetOptionValueMap(OptionValueMap const&);

	void AddOptionAndValue(EOption const, SOptionValue const&);

private:
	EOperation m_eCommandType = EOperation::Invalid;
	OptionValueMap m_aOptions;
};
//////////////////////////////////////////////////////////////////////

} // namespace Command
//////////////////////////////////////////////////////////////////////
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMAND_HPP_
