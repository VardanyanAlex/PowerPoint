
#ifndef _POWERPOINT_INTERFACE_ICOMMANDLINE_HPP_
#define _POWERPOINT_INTERFACE_ICOMMANDLINE_HPP_

#include <iostream>
#include <memory>

#include "pwpt_icommand.h"

namespace pwpt
{

using ICommandLine_Ptr = std::unique_ptr<Command::ICommandLine>;

namespace Command
{

class ICommandLine
{
public:
	using DataStream_Ptr = std::unique_ptr<std::istream>;

	virtual void Run() = 0;
	virtual void ProcessInput(DataStream_Ptr) = 0;
//signals:
	virtual void commandConstructed(ICommand_Ptr) = 0;

}; // interface ICommandLine

} // namespace Command

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMANDLINE_HPP_
