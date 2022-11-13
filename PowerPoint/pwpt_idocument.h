
#ifndef _POWERPOINT_INTERFACE_DOCUMENT_HPP_
#define _POWERPOINT_INTERFACE_DOCUMENT_HPP_

#include <memory>

#include "console.h"
#include "pwpt_islidecontainer.h"

namespace pwpt
{

namespace Document
{

enum class ETool
{
	Line,
	Rectangle,
	Triangle,
	Circular,
	TextBox
};

enum class ESize
{
	Small,
	Medium,
	Big
};

class IDocument
{
public:
	virtual SlideContainer_SharedPtr GetSlideShow() = 0;
	virtual Slide_SharedPtr GetSlide(size_t iIndex) = 0;
	virtual size_t& GetCurrentSlideIndex() = 0;
	
	virtual ETool& GetTool() = 0;
	virtual ESize& GetLineWidth() = 0;

}; // interface IDocument

} // namespace Document
using PwPtDoc_ptr = std::shared_ptr<class Document::IDocument>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_DOCUMENT_HPP_
