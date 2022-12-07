
#include <string>

#include "commandscomponents.h"

namespace pwpt
{

SOptionValue::SOptionValue(std::string const& sValue)
	: m_sTextValue{ sValue }
{}

SOptionValue::SOptionValue(int const iValue)
	: m_iNumberValue{ iValue }
{}

bool SOptionValue::IsValueNumber() const 
{
	return (m_iNumberValue >= 0 && m_sTextValue.empty());
}

bool SOptionValue::IsValueText() const
{
	return (!m_sTextValue.empty() && m_iNumberValue < 0);
}

void SOptionValue::SetNumber(int iValue)
{
	m_iNumberValue = iValue;
	m_sTextValue.clear();
}

void SOptionValue::SetText(std::string const& sValue)
{
	m_sTextValue = sValue;
	m_iNumberValue = -1;
}

bool SOptionValue::IsValid() const
{
	return IsValueNumber() || IsValueText();
}

} // namespace pwpt
