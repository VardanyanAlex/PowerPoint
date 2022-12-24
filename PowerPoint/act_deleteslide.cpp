
#include "act_addslide.h"
#include "act_deleteslide.h"
#include "pwpt_appmanager.h"

namespace pwpt
{

CDeleteSlide::CDeleteSlide(int iPositionInSlideshow)
	: m_pSlide{ nullptr }
	, m_pSlideshow{ nullptr }
	, m_iPositionInSlideshow{ iPositionInSlideshow }
{}

void CDeleteSlide::Run()
{
	m_pSlide = m_pSlideshow->GetSlide(m_iPositionInSlideshow);

	m_pSlideshow->Remove(m_iPositionInSlideshow);
}

bool CDeleteSlide::CanRun() const
{
	auto pDoc = App::CAppManager::AppInstance().GetDocument();
	if (pDoc == nullptr)
		return false;

	m_pSlideshow = pDoc->GetSlideShow();

	return m_iPositionInSlideshow >= 0 && m_pSlideshow != nullptr;
}

IAction_SPtr CDeleteSlide::Reverse() const
{
	IAction_SPtr pActReverse = std::make_shared<CAddSlide>(m_iPositionInSlideshow);

	return pActReverse;
}

void CDeleteSlide::SetWorkingSlideshow(ISlideContainer_SPtr pSlideshow)
{
	m_pSlideshow = pSlideshow;
}

} // namespace pwpt
