
#include <string>

#include "act_addslide.h"
#include "cmd_add.h"
#include "pwpt_appmanager.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 

CAddCmd::CAddCmd()
{
	m_aAcceptedOptions = { "--slide" };
}

void CAddCmd::Execute()
{
	auto& oApp = App::CAppManager::AppInstance();

	PwPtDoc_SPtr pDoc = App::CAppManager::AppInstance().GetDocument();
	if (pDoc == nullptr)
		throw CCmdExecException{ "Application's document is invalid" };

	if (m_sMainOption == "--slide")
	{
		auto pSlideShow = pDoc->GetSlideShow();
		if (pSlideShow == nullptr)
			throw CCmdExecException{ "The slideshow is invalid!!!" };

		IAction_SPtr pAddSlide = nullptr;
		if (m_aOptValues.empty())
		{
			pAddSlide = std::make_shared<CAddSlide>();
		}
		else
		{
			if (m_aOptValues.contains("-index"))
			{
				int iSlideIndex = std::any_cast<int>(m_aOptValues["-index"]);

				pAddSlide = std::make_shared<CAddSlide>(iSlideIndex);
			}
		}

		if (pAddSlide != nullptr)
			emit CreatedAction(pAddSlide);

	}
}

ICommand_SPtr CAddCmd::Clone() const
{
	return std::make_shared<CAddCmd>(*this);
}

bool CAddCmd::MainOptionRequired() const
{
	return true;
}

size_t CAddCmd::RequiredMinOptionsCount() const
{
	return 0;
}

bool CAddCmd::Acceptarg(std::string const& sOption, std::any oValue)
{
	bool bIsAcceptedOption = false;

	if (m_sMainOption.empty())
		return bIsAcceptedOption;

	try
	{
		if (m_sMainOption == "--slide")
		{
			if (sOption == "-index")
			{
				int iValue = std::any_cast<int>(oValue);
				
				m_aOptValues.emplace(sOption, iValue);
				bIsAcceptedOption = true;
				
			}
		}
	}
	catch (...)
	{
		bIsAcceptedOption = false;
	}
		
	return bIsAcceptedOption;
}

bool CAddCmd::Validate() const
{
	return true;
}

} // namespace Command

} // namespace pwpt
