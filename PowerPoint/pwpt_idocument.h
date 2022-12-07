
#ifndef _POWERPOINT_INTERFACE_DOCUMENT_HPP_
#define _POWERPOINT_INTERFACE_DOCUMENT_HPP_

#include <memory>

#include "console.h"
#include "pwpt_islidecontainer.h"
#include "tools.h"

namespace pwpt
{

namespace Document
{

class IDocument
{
public:
	virtual SlideContainer_SPtr GetSlideShow() = 0;
	virtual Slide_SPtr GetSlide(size_t const iIndex) = 0;
	virtual size_t GetCurrentSlideIndex() = 0;
	virtual size_t SetSlide(size_t const iIndex) = 0;
	
	virtual EShape GetShape() = 0;
	virtual void SetShape(EShape const) = 0;

	virtual ELineThickness GetLineThickness() = 0;
	virtual void SetLineThickness(ELineThickness const) = 0;

	virtual QColor GetColor() = 0;
	virtual void SetColor(QColor const) = 0;

}; // interface IDocument

} // namespace Document
using PwPtDoc_SPtr = std::shared_ptr<class Document::IDocument>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_DOCUMENT_HPP_
