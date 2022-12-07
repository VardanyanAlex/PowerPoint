
#ifndef _POWERPOINT_INTERFACE_ICOMMAND_HPP_
#define _POWERPOINT_INTERFACE_ICOMMAND_HPP_

#include <any>
#include <memory>
#include <queue>

#include "pwpt_ioutputdevice.h"
#include "token.h"

namespace pwpt
{

namespace Command
{ 
//////////////////////////////////////////////////////////////
/// Interface ICommand
//////////////////////////////////////////////////////////////
class ICommand
{
public:
	virtual void Execute() = 0;
	virtual std::shared_ptr<ICommand> Clone() const = 0;
	virtual bool Acceptarg(std::string const&, std::any oValue) = 0;
	virtual bool Validate() const = 0;

	bool operator==(ICommand const&);
	/*virtual SOptionValue GetValue(EOption) const = 0;
	
	virtual EOption GetMainOption() const = 0;

	virtual OptionValueMap GetOptions() const = 0;*/

protected:
	std::vector<std::string> m_aAcceptedOptions;
	std::map<std::string, std::any> m_aOptValues;
};
//////////////////////////////////////////////////////////////
} // namespace Command
using ICommand_SPtr = std::shared_ptr<class Command::ICommand>;
using ICommandsList = std::queue<ICommand_SPtr>;
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMAND_HPP_
