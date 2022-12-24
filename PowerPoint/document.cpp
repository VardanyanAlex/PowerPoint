
#include "document.h"
#include "slideshow.h"

namespace pwpt
{

namespace Document
{

CPwPtDocument::CPwPtDocument()
	: m_pSlideShow{ nullptr }
	, m_nActiveSlideIndex{ 0 }
	, m_eSelectedShape{ CShape::EShape::None }
	, m_oSelectedColor{ Qt::black }
	, m_eLineThickness{ ELineThickness::Medium }
{
	m_pSlideShow = std::make_shared<CSlideShow>();
}

ISlideContainer_SPtr CPwPtDocument::GetSlideShow()
{
	return m_pSlideShow;
}

int CPwPtDocument::GetActiveSlideIndex() const
{
	return m_nActiveSlideIndex;
}

void CPwPtDocument::SetActiveSlide(size_t const iIndex)
{
	m_nActiveSlideIndex = iIndex;
}

CShape CPwPtDocument::GetShape()
{
	return m_eSelectedShape;
}

void CPwPtDocument::SetShape(CShape const& eShape)
{
	m_eSelectedShape = eShape;
}

ELineThickness CPwPtDocument::GetLineThickness() const
{
	return m_eLineThickness;
}

void CPwPtDocument::SetLineThickness(ELineThickness const eThickness)
{
	m_eLineThickness = eThickness;
}

QColor CPwPtDocument::GetColor() const
{
	return m_oSelectedColor;
}

void CPwPtDocument::SetColor(QColor const oColor)
{
	m_oSelectedColor = oColor;
}

} // namespace Document

} // namespace pwpt
