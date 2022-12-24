
#ifndef _POWERPOINT_INTERFACE_DOCUMENT_HPP_
#define _POWERPOINT_INTERFACE_DOCUMENT_HPP_

#include <memory>

#include <QColor>

#include "pwpt_islidecontainer.h"
#include "shape.h"
#include "tools.h"

namespace pwpt
{

namespace Document
{

class IDocument
{
public:
	virtual ISlideContainer_SPtr GetSlideShow() = 0;
	virtual int GetActiveSlideIndex() const = 0;
	virtual void SetActiveSlide(size_t const iIndex) = 0;
	
	virtual CShape GetShape() = 0;
	virtual void SetShape(CShape const&) = 0;

	virtual ELineThickness GetLineThickness() const = 0;
	virtual void SetLineThickness(ELineThickness const) = 0;

	virtual QColor GetColor() const = 0;
	virtual void SetColor(QColor const) = 0;

}; // interface IDocument

} // namespace Document
using PwPtDoc_SPtr = std::shared_ptr<class Document::IDocument>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_DOCUMENT_HPP_
