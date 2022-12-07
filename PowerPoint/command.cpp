
#include <iostream>
#include <string>

#include "application.h"
#include "command.h"
#include "outputconsole.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 

//EOperation CCommand::GetCommandType() const
//{
//	return m_eCommandType;
//}
//
//EOption CCommand::GetMainOption() const
//{
//	return m_eMainOption;
//}
//
//OptionValueMap CCommand::GetOptions() const
//{
//	return m_aOptions;
//}
//
//SOptionValue CCommand::GetValue(EOption const eOption) const
//{
//	return m_aOptions.at(eOption);
//}
//
//void CCommand::SetCommandType(EOperation const eOp)
//{
//	m_eCommandType = eOp;
//}
//
//void CCommand::SetOptionValueMap(OptionValueMap const& aOptions)
//{
//	m_aOptions = aOptions;
//}
//
//void CCommand::SetMainOption(EOption eOption)
//{
//	m_eMainOption = eOption;
//}
//
//void CCommand::AddOptionAndValue(EOption const eOption, SOptionValue const& oValue)
//{
//	m_aOptions.insert({eOption, oValue});
//}

PrintCmd::PrintCmd()
{
	m_aAcceptedOptions = { "--slide", "--object"};
}

void PrintCmd::Execute()
{
	OutputStream_SPtr pStream = std::dynamic_pointer_cast<COutputStream>(pOutput);

	PwPtDoc_SPtr pDoc = App::CApplication::Instance().GetDocument();

	Slide_SPtr pSlide = pDoc->GetSlide(1);

	auto aObjects = pSlide->GetObjects();

	for (auto const& oObject : aObjects)
	{
		pStream->Draw(oObject);
	}
}

ICommand_SPtr PrintCmd::Clone() const
{
	return std::make_shared<PrintCmd>(*this);
}

bool PrintCmd::Acceptarg(std::string const& sOption, std::any oValue)
{
	bool bIsAcceptedOption = false;

	auto it = std::find(m_aAcceptedOptions.begin(), m_aAcceptedOptions.end(), sOption);

	if (it != m_aAcceptedOptions.end())
	{
		try
		{
			if (sOption == "--slide")
			{
				if (oValue.type().name() == "string")
				{
					std::string sValue = std::any_cast<std::string>(oValue);
					if (sValue == "-current")
					{
						m_aOptValues.emplace(sOption, oValue);
						bIsAcceptedOption = true;
					}
				}
				else if (oValue.type().name() == "int")
				{
					int iValue = std::any_cast<int>(oValue);
					if (iValue > 0)
					{
						m_aOptValues.emplace(sOption, oValue);
						bIsAcceptedOption = true;
					}
				}
			}
			else if (sOption == "--object"/* && oValue.type().name() == "string"*/)
			{
				std::string sValue = std::any_cast<std::string>(oValue);
				if(sValue == "-count")
				{
					m_aOptValues.emplace(sOption, oValue);
					bIsAcceptedOption = true;
				}
			}
		}
		catch (std::exception const& ex)
		{
			return bIsAcceptedOption;
		}
		
	}
	return bIsAcceptedOption;
}

bool PrintCmd::Validate() const
{
	return true;
}

} // namespace Command

} // namespace pwpt
