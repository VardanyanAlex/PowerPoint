
#include "errorhandling.h"

CError::CError(std::string const& sErrorMsg)
	: m_sErrorMsg{ sErrorMsg }
{}

char const* CError::what() const
{
	return m_sErrorMsg.c_str();
}
