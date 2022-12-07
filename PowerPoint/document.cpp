
#include "document.h"

namespace pwpt
{

namespace Document
{

SlideContainer_SPtr CPwPtDocument::GetSlideShow()
{
	return m_pSlideShow;
}

Slide_SPtr CPwPtDocument::GetSlide(size_t iIndex)
{
	Slide_SPtr pSlide = nullptr;

	assert(m_pSlideShow != nullptr);
	if(m_pSlideShow != nullptr)
		pSlide = m_pSlideShow->GetSlide(iIndex);

	return pSlide;
}

size_t CPwPtDocument::GetCurrentSlideIndex()
{
	return m_nCurrentSlideIndex;
}

EShape CPwPtDocument::GetShape()
{
	return m_eSelectedShape;
}

ELineThickness CPwPtDocument::GetLineThickness()
{
	return m_eLineThickness;
}

} // namespace Document

} // namespace pwpt
