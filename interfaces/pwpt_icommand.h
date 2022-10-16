
#ifndef _POWERPOINT_INTERFACE_ICOMMAND_HPP_
#define _POWERPOINT_INTERFACE_ICOMMAND_HPP_

#include <memory>

namespace pwpt
{

using ICommand_Ptr = std::unique_ptr<Command::ICommand>;

namespace Command
{ 

class ICommand
{
public:

};

} // namespace Command

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMAND_HPP_
