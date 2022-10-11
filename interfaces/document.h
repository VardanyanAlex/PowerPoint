
#ifndef _POWERPOINT_MACHINE_HPP_
#define _POWERPOINT_MACHINE_HPP_

#include <memory>

#include "console.h"
#include "slideshow.h"

namespace Document
{

enum class ETool
{
	eLine,
	eRectangle,
	eTriangle,
	eCircular,
	eTextBox
};

enum class ESize
{
	eSmall,
	eMedium,
	eBig
};

class CPwPtDocument
{
public:
	CPwPtDocument();

	std::shared_ptr<CSlideShow> GetSlideShow();

	void SetTool();
	ETool Tool();

	void SetLineWidth(ESize);
	ESize LineWidth();

private:
	std::unique_ptr<CSlideShow> m_pSlideShow;
	ETool						m_eSelectedTool;
	//QColor					m_oSelectedColor;
	ESize						m_eLineWidth;

}; // class CPwPtDocument

} // namespace Document

#endif // _POWERPOINT_MACHINE_HPP_
