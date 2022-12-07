
#ifndef _POWERPOINT_MAIN_DOCUMENT_HPP_
#define _POWERPOINT_MAIN_DOCUMENT_HPP_

#include "console.h"
#include "pwpt_islidecontainer.h"
#include "pwpt_idocument.h"

namespace pwpt
{

namespace Document
{

class CPwPtDocument : public IDocument
{
public:
	CPwPtDocument() = default;
	CPwPtDocument(CPwPtDocument const&) = delete;
	CPwPtDocument& operator=(CPwPtDocument const&) = delete;

	SlideContainer_SPtr GetSlideShow() override;
	Slide_SPtr GetSlide(size_t iIndex) override;
	size_t GetCurrentSlideIndex() override;

	EShape GetShape() override;
	ELineThickness GetLineThickness() override;

private:
	pwpt::SlideContainer_SPtr	m_pSlideShow;
	size_t						m_nCurrentSlideIndex;
	EShape						m_eSelectedShape;
	//QColor					m_oSelectedColor;
	ELineThickness				m_eLineThickness;

}; // class CPwPtDocument

} // namespace Document

} // namespace pwpt

#endif // _POWERPOINT_MAIN_DOCUMENT_HPP_
