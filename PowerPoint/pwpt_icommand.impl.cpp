
#include "pwpt_icommand.h"

namespace pwpt
{

namespace Command
{ 

ICommand::ICommand(ICommand const& oCommand)
{
	m_aAcceptedOptions = oCommand.m_aAcceptedOptions;
	m_sMainOption = oCommand.m_sMainOption;
	m_aOptValues = oCommand.m_aOptValues;
};

bool ICommand::AcceptMainOption(std::string const& sOption)
{
	bool bAccepted = std::find(m_aAcceptedOptions.begin(), m_aAcceptedOptions.end(), sOption) != m_aAcceptedOptions.end();

	if (bAccepted)
		m_sMainOption = sOption;

	return bAccepted;
}

CCmdExecException::CCmdExecException(std::string const& sErrorMessage)
	: m_sErrorMessage{ sErrorMessage + "\n\n" }
{}

const char* CCmdExecException::what() const noexcept
{
	return m_sErrorMessage.c_str();
}

} // namespace Command

} // namespace pwpt
