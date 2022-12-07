
#ifndef _POWERPOINT_COMMAND_FACTORY_HPP_
#define _POWERPOINT_COMMAND_FACTORY_HPP_

#include <unordered_map>

#include "pwpt_icommand.h"

namespace pwpt
{

namespace Command
{

class CFactory
{
public:
	CFactory(CFactory const&) = delete;
	CFactory& operator=(CFactory const&) = delete;

	static CFactory& GetInstance();

	pwpt::ICommand_SPtr CreateCommand(std::string) const;

private:
	CFactory();

private:
	std::unordered_map<std::string, pwpt::ICommand_SPtr> m_aCommands;
};

} // namespace Command

} // namespace pwpt

#endif // _POWERPOINT_COMMAND_FACTORY_HPP_
