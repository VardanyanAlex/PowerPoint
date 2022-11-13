
#ifndef _POWERPOINT_INTERFACE_ICOMMAND_HPP_
#define _POWERPOINT_INTERFACE_ICOMMAND_HPP_

#include <memory>
#include <queue>

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
	virtual EOperation GetCommandType() const = 0;
	virtual SOptionValue GetValue(EOption) const = 0;
	
	virtual OptionValueMap GetOptions() const = 0;

};
//////////////////////////////////////////////////////////////
} // namespace Command
using ICommand_Ptr = std::shared_ptr<class Command::ICommand>;
using ICommandsList = std::queue<ICommand_Ptr>;
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMAND_HPP_
