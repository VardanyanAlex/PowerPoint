
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

class PrintCmd : public ICommand
{
public:
	PrintCmd();

	void Execute() override;
	std::shared_ptr<ICommand> Clone() const override;
	bool Acceptarg(std::string const&, std::any oValue) override;
	bool Validate() const override;
};

//class SetCmd : public ICommand
//{
//public:
//	void Execute(OutputDevice_SPtr&) override;
//	ICommand_SPtr Clone() const override;
//	bool Acceptarg(std::string const&, std::any oValue) override;
//	bool Validate() const override;
//};
//
//class ResetCmd : public ICommand
//{
//public:
//	void Execute(OutputDevice_SPtr&) override;
//	ICommand_SPtr Clone() const override;
//	bool Acceptarg(std::string const&, std::any oValue) override;
//	bool Validate() const override;
//};

} // namespace Command
//////////////////////////////////////////////////////////////////////
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMAND_HPP_
