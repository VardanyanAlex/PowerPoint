
#ifndef _POWERPOINT_MAIN_DOCUMENT_HPP_
#define _POWERPOINT_MAIN_DOCUMENT_HPP_

#include "pwpt_islidecontainer.h"
#include "pwpt_idocument.h"

namespace pwpt
{

namespace Document
{

class CPwPtDocument : public IDocument
{
public:
	CPwPtDocument();
	CPwPtDocument(CPwPtDocument const&) = delete;
	CPwPtDocument& operator=(CPwPtDocument const&) = delete;

	ISlideContainer_SPtr GetSlideShow() override;
	int GetActiveSlideIndex() const override;
	void SetActiveSlide(size_t const iIndex) override;
	
	CShape GetShape() override;
	void SetShape(CShape const&) override;
	
	ELineThickness GetLineThickness() const override;
	void SetLineThickness(ELineThickness const) override;
	
	QColor GetColor() const override;
	void SetColor(QColor const) override;

private:
	pwpt::ISlideContainer_SPtr	m_pSlideShow;
	int							m_nActiveSlideIndex;
	CShape						m_eSelectedShape;
	QColor						m_oSelectedColor;
	ELineThickness				m_eLineThickness;

}; // class CPwPtDocument

} // namespace Document

} // namespace pwpt

#endif // _POWERPOINT_MAIN_DOCUMENT_HPP_
