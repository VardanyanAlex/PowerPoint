
#include "pwpt_ipainter.h"

namespace pwpt
{

CUnavailableOutputDevice::CUnavailableOutputDevice(std::string const& sErrorMessage)
	: m_sErrorMessage{ sErrorMessage + "\n\n" }
{}

const char* CUnavailableOutputDevice::what() const noexcept
{
	return m_sErrorMessage.c_str();
}

} // namespace pwpt
