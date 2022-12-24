
#ifndef _POWERPOINT_COMMAND_UNDO_HPP_
#define _POWERPOINT_COMMAND_UNDO_HPP_

#include "pwpt_icommand.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 
//////////////////////////////////////////////////////////////////////

class CUndoCmd : public ICommand
{
public:
	CUndoCmd();
	CUndoCmd(CUndoCmd const&) = default;

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

#endif // _POWERPOINT_COMMAND_UNDO_HPP_
