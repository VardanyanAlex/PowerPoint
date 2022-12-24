
#include "streampainter.h"

namespace pwpt
{

CStreamPainter::CStreamPainter(std::ostream* pOstream)
	: m_pOutput{ pOstream }
{}

void CStreamPainter::Draw(CShape const& oShape, double x1, double y1, double x2, double y2, QColor oColor)
{
	if (m_pOutput == nullptr)
		throw CUnavailableOutputDevice{ "Output device not set or is unavailable!!!" };

	*m_pOutput << oShape.ToString();
	PrintGeometry(x1, y1, x2, y2);
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::Draw(CShape const& oShape, QPointF const& p1, QPointF const& p2, QColor oColor)
{
	Draw(oShape, p1.x(), p1.y(), p2.x(), p2.y(), oColor);
}

void CStreamPainter::DrawLine(double x1, double y1, double x2, double y2, QColor oColor)
{
	Draw(CShape{CShape::EShape::Line}, x1, y1, x2, y2, oColor);
}
void CStreamPainter::DrawLine(QPointF const& p1, QPointF const& p2, QColor oColor)
{
	Draw(CShape{ CShape::EShape::Line }, p1.x(), p1.y(), p2.x(), p2.y(), oColor);
}

void CStreamPainter::DrawRect(double x1, double y1, double x2, double y2, QColor oColor)
{
	Draw(CShape{ CShape::EShape::Rectangle }, x1, y1, x2, y2, oColor);
}

void CStreamPainter::DrawRect(QPointF const& p1, QPointF const& p2, QColor oColor)
{
	Draw(CShape{ CShape::EShape::Rectangle }, p1.x(), p1.y(), p2.x(), p2.y(), oColor);
}

void CStreamPainter::DrawEclipse(double x1, double y1, double x2, double y2, QColor oColor)
{
	Draw(CShape{ CShape::EShape::Circular }, x1, y1, x2, y2, oColor);
}

void CStreamPainter::DrawEclipse(QPointF const& p1, QPointF const& p2, QColor oColor)
{
	Draw(CShape{ CShape::EShape::Circular }, p1.x(), p1.y(), p2.x(), p2.y(), oColor);
}

void CStreamPainter::DrawText(double x1, double y1, double x2, double y2, QString const& sText, QColor oColor)
{
	Draw(CShape{ CShape::EShape::TextBox }, x1, y1, x2, y2, oColor);
}

void CStreamPainter::DrawText(QPointF const& p1, QPointF const& p2, QString const& sText, QColor oColor)
{
	Draw(CShape{ CShape::EShape::TextBox }, p1.x(), p1.y(), p2.x(), p2.y(), oColor);
}

void CStreamPainter::PrintGeometry(double x1, double y1, double x2, double y2)
{
	if (m_pOutput == nullptr)
		throw CUnavailableOutputDevice{ "Output device not set or is unavailable!!!" };

	*m_pOutput << " (" << x1 << "," << y1 << ")" << " " << "(" << x2 << "," << y2 << ") ";
}

} // namespace pwpt
