
#include "errorhandling.h"
#include "pwpt_iaction.h"

namespace pwpt
{

CActionExecException::CActionExecException(std::string const& sErrorMessage)
	: m_sErrorMessage{ sErrorMessage + "\n\n"}
{
}

const char* CActionExecException::what() const noexcept
{
	return m_sErrorMessage.c_str();
}

} // namespace pwpt
