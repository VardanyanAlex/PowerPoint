
#ifndef _POWERPOINT_COMMAND_PRINT_HPP_
#define _POWERPOINT_COMMAND_PRINT_HPP_

#include "pwpt_icommand.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 
//////////////////////////////////////////////////////////////////////

class PrintCmd : public ICommand
{
public:
	PrintCmd();
	PrintCmd(PrintCmd const&) = default;

	void Execute() override;
	ICommand_SPtr Clone() const override;

	bool MainOptionRequired() const override;
	size_t RequiredMinOptionsCount() const override;

	bool Acceptarg(std::string const&, std::any oValue) override;
	bool Validate() const override;
};

} // namespace Command
//////////////////////////////////////////////////////////////////////
} // namespace pwpt

#endif // _POWERPOINT_COMMAND_PRINT_HPP_