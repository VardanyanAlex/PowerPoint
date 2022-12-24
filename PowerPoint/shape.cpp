
#include "shape.h"

namespace pwpt
{

CShape::CShape(CShape::EShape eShape)
	: m_eShape{ EShape::None }
	, m_sShape{ "None" }
{
	SetShape(eShape);
}

CShape::CShape(std::string const& sShape)
	: m_eShape{ EShape::None }
	, m_sShape{ "None" }
{
	SetShape(sShape);
}

std::string CShape::ToString() const
{
	return m_sShape;
}

CShape::EShape CShape::GetShape() const
{
	return m_eShape;
}

void CShape::SetShape(EShape eShape)
{
	m_eShape = eShape;

	switch (m_eShape)
	{
	case EShape::Line:
		m_sShape = "Line";
		break;
	case EShape::Rectangle:
		m_sShape = "Rectangle";
		break;
	case EShape::Triangle:
		m_sShape = "Triangle";
		break;
	case EShape::Circular:
		m_sShape = "Circular";
		break;
	case EShape::TextBox:
		m_sShape = "TextBox";
		break;
	default:
		m_sShape = "None";
		break;
	}
}

void CShape::SetShape(std::string const& sShape)
{
	m_sShape = sShape;

	if (sShape == "Line")
		m_eShape = EShape::Line;
	else if (sShape == "Rectangle")
		m_eShape = EShape::Rectangle;
	else if (sShape == "Triangle")
		m_eShape = EShape::Triangle;
	else if (sShape == "Circular")
		m_eShape = EShape::Circular;
	else if (sShape == "TextBox")
		m_eShape = EShape::TextBox;
	else
		m_eShape = EShape::None;
}

} // namespace pwpt
