
#include <cassert>

#include "errorhandling.h"
#include "toolbar_actions.h"

namespace pwpt
{ 

///////////////////////////////////////////////////////////////////////
// CShapeChanger impl

CShapeChanger::CShapeChanger(EShape const eShape)
	: m_eShape{ eShape }
{}

void CShapeChanger::Run()
{
	CheckDocumentValidity();

	m_pDoc->SetShape(m_eShape);
}

///////////////////////////////////////////////////////////////////////
// CThicknessChanger impl

CThicknessChanger::CThicknessChanger(ELineThickness const eThickness)
	: m_eThickness{ eThickness }
{}

void CThicknessChanger::Run()
{
	CheckDocumentValidity();

	m_pDoc->SetLineThickness(m_eThickness);
}

///////////////////////////////////////////////////////////////////////
// CColorChanger impl

CColorChanger::CColorChanger(QColor const oColor)
	: m_oColor{ oColor }
{}

void CColorChanger::Run()
{
	CheckDocumentValidity();

	m_pDoc->SetColor(m_oColor);
}

} // namespace pwpt
