
#ifndef _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_
#define _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_

#include <memory>

#include "pwpt_icommand.h"

namespace pwpt
{

using ICommandHandler_Ptr = std::unique_ptr<Command::IHandler>;

namespace Command
{ 

enum class EState
{
	success,
	failure
};

class IHandler
{
public:
	virtual void SetEditor(CEditor&) = 0;
	
	virtual EState Handle(ICommand_Ptr) = 0;

//signals:
	virtual void actionConstructed(IACtion_Ptr) = 0;

//public slots:
	virtual void OnCommandConstructed(ICommand_Ptr) = 0;

}; // interface IMachine

} // namespace Command

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_
