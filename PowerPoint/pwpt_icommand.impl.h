
#include "pwpt_icommand.h"

namespace pwpt
{

namespace Command
{ 

bool ICommand::operator==(ICommand const& oCmdRHS)
{
	return m_aAcceptedOptions == oCmdRHS.m_aAcceptedOptions && m_aOptValues == oCmdRHS.m_aOptValues;
}

} // namespace Command

} // namespace pwpt
