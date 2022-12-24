
#ifndef _POWERPOINT_COMMAND_REDO_HPP_
#define _POWERPOINT_COMMAND_REDO_HPP_

#include "pwpt_icommand.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{
//////////////////////////////////////////////////////////////////////

class CRedoCmd : public ICommand
{
public:
	CRedoCmd();
	CRedoCmd(CRedoCmd const&) = default;

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

#endif // _POWERPOINT_COMMAND_REDO_HPP_
