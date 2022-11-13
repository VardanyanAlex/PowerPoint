
#ifndef _POWERPOINT_MACHINE_HPP_
#define _POWERPOINT_MACHINE_HPP_

#include <memory>

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
	CPwPtDocument() =default;

	SlideContainer_SharedPtr GetSlideShow() override;
	Slide_SharedPtr GetSlide(size_t iIndex) override;
	size_t& GetCurrentSlideIndex() override;

	ETool& GetTool() override;
	ESize& GetLineWidth() override;

private:
	pwpt::SlideContainer_Ptr	m_pSlideShow;
	size_t						m_nCurrentSlideIndex;
	ETool						m_eSelectedTool;
	//QColor					m_oSelectedColor;
	ESize						m_eLineWidth;

}; // class CPwPtDocument

} // namespace Document

} // namespace pwpt

#endif // _POWERPOINT_MACHINE_HPP_
