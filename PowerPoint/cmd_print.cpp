
#include <iostream>
#include <string>

#include "cmd_print.h"
#include "pwpt_app.h"
#include "pwpt_appmanager.h"
#include "streampainter.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 

PrintCmd::PrintCmd()
{
	m_aAcceptedOptions = { "--slide", "--object" };
}

void PrintCmd::Execute()
{
	auto& oApp = App::CAppManager::AppInstance();

	PwPtDoc_SPtr pDoc = App::CAppManager::AppInstance().GetDocument();
	if (pDoc == nullptr)
		throw CCmdExecException{ "Application's document is invalid" };

	std::ostream* pOutput =  oApp.GetOutputStreamDevice();
	if (pOutput != nullptr)
	{
		if (m_sMainOption == "--slide")
		{
			auto pSlideShow = pDoc->GetSlideShow();
			if (pSlideShow == nullptr)
				throw CCmdExecException{ "Unexpected error occured!!!" };
			
			if (m_aOptValues.empty())
			{
				int iCurrentSlideIdx = pDoc->GetActiveSlideIndex();

				if(iCurrentSlideIdx == 0)
					throw CCmdExecException{ "You don't have active slide!" };

				auto pSlide = pSlideShow->GetSlide(iCurrentSlideIdx);
				if (pSlide == nullptr)
					throw CCmdExecException{ "invalid slide detected!" };

				ObjectList aObjects =  pSlide->GetObjects();

				CStreamPainter oPainter{ pOutput };
				for (auto const& pObject : aObjects)
				{
					oPainter.Draw(pObject->GetShape(), pObject->GetGeometry().first, pObject->GetGeometry().second, pObject->GetColor());
				}
			}
		}
	}
}

ICommand_SPtr PrintCmd::Clone() const
{
	return std::make_shared<PrintCmd>(*this);
}

bool PrintCmd::MainOptionRequired() const
{
	return true;
}

size_t PrintCmd::RequiredMinOptionsCount() const
{
	return 0;
}

bool PrintCmd::Acceptarg(std::string const& sOption, std::any oValue)
{
	bool bIsAcceptedOption = false;

	if (m_sMainOption.empty())
		return bIsAcceptedOption;

	try
	{
		if (m_sMainOption == "--slide")
		{
			if (sOption == "-object")
			{
				std::string sValue = std::any_cast<std::string>(oValue);
				
				if (sValue == "count")
				{
					m_aOptValues.emplace(sOption, sValue);
					bIsAcceptedOption = true;
				}
			}
			else if (sOption == "-index")
			{
				int iValue = std::any_cast<int>(oValue);

				if (iValue > 0)
				{
					m_aOptValues.emplace(sOption, iValue);
					bIsAcceptedOption = true;
				}
			}
		}
	}
	catch (...)
	{
		bIsAcceptedOption = false;
	}
		
	return bIsAcceptedOption;
}

bool PrintCmd::Validate() const
{
	return true;
}

} // namespace Command

} // namespace pwpt
