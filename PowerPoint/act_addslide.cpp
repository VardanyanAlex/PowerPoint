
#include "act_addslide.h"
#include "act_deleteslide.h"
#include "pwpt_appmanager.h"
#include "slide.h"

namespace pwpt
{

CAddSlide::CAddSlide(int iPositionInSlideshow)
	: m_pSlide{ nullptr }
	, m_pSlideshow{ nullptr }
	, m_iNewSlideIndex{ iPositionInSlideshow }
{}

void CAddSlide::Run()
{
	if (m_pSlideshow == nullptr)
		throw CActionExecException{ "slideshow wasn't set!!!" };

	if(m_pSlide == nullptr)
		m_pSlide = std::make_shared<CSlide>();
	
	auto pDoc = App::CAppManager::AppInstance().GetDocument();
	if (pDoc == nullptr)
		throw CActionExecException{ "Unexpected error occurred!!!" };

	if (m_iNewSlideIndex == 0)
	{
		m_pSlideshow->Add(m_pSlide);
		pDoc->SetActiveSlide(1);
		m_iNewSlideIndex = 1;
	}
	else
	{
		m_pSlideshow->Insert(m_pSlide, m_iNewSlideIndex);
	}
	
}

bool CAddSlide::CanRun() const
{
	auto pDoc = App::CAppManager::AppInstance().GetDocument();
	if (pDoc == nullptr)
		return false;

	m_pSlideshow = pDoc->GetSlideShow();

	return (m_iNewSlideIndex >= 0) && (m_pSlideshow != nullptr);
}

IAction_SPtr CAddSlide::Reverse() const
{
	IAction_SPtr pActReverse = std::make_shared<CDeleteSlide>(m_iNewSlideIndex);

	return pActReverse;
}

} // namespace pwpt
