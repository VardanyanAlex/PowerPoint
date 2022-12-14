
#include "streampainter.h"

namespace pwpt
{

CStreamPainter::CStreamPainter(std::shared_ptr<std::ostream> pPaintDevice)
	: m_pOutput{ pPaintDevice }
{}

void CStreamPainter::DrawLine(double x1, double y1, double x2, double y2, QColor oColor)
{
	*m_pOutput << "Line ";
	PrintGeometry(x1, y1, x2, y2);
	*m_pOutput << oColor.name().toStdString()
}
void CStreamPainter::DrawLine(QPointF const& p1, QPointF const& p2, QColor oColor)
{
	*m_pOutput << "Line ";
	PrintGeometry(p1.x(), p1.y(), p2.x(), p2.y());
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::DrawRect(double x1, double y1, double x2, double y2, QColor oColor)
{
	*m_pOutput << "Rect ";
	PrintGeometry(x1, y1, x2, y2);
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::DrawRect(QPointF const& p1, QPointF const& p2, QColor oColor)
{
	*m_pOutput << "Rect ";
	PrintGeometry(p1.x(), p1.y(), p2.x(), p2.y());
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::DrawEclipse(double x1, double y1, double x2, double y2, QColor oColor)
{
	*m_pOutput << "Eclipse ";
	PrintGeometry(x1, y1, x2, y2);
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::DrawEclipse(QPointF const& p1, QPointF const& p2, QColor oColor)
{
	*m_pOutput << "Eclipse ";
	PrintGeometry(p1.x(), p1.y(), p2.x(), p2.y());
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::DrawText(double x1, double y1, double x2, double y2, QString const& sText, QColor oColor)
{
	*m_pOutput << "Text ";
	PrintGeometry(x1, y1, x2, y2);
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::DrawText(QPointF const& p1, QPointF const& p2, QString const& sText, QColor oColor)
{
	*m_pOutput << "Text ";
	PrintGeometry(p1.x(), p1.y(), p2.x(), p2.y());
	*m_pOutput << oColor.name().toStdString();
}

void CStreamPainter::PrintGeometry(double x1, double y1, double x2, double y2)
{
	*m_pOutput << "(" << x1 << "," << y1 << ")" << " " << "(" << x2 << "," << y2 << ")";
}

} // namespace pwpt
