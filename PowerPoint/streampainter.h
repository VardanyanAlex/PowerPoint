
#ifndef _POWERPOINT_STREAM_PAINTER_HPP_
#define _POWERPOINT_STREAM_PAINTER_HPP_

#include <iostream>
#include <memory>

#include "pwpt_ipainter.h"

namespace pwpt
{

class CStreamPainter : public IPainter
{
public:
	CStreamPainter(std::ostream* = &std::cout);

	void Draw(CShape const&, double x1, double y1, double x2, double y2, QColor = Qt::black) override;
	void Draw(CShape const&, QPointF const& p1, QPointF const& p2, QColor = Qt::black) override;

	void DrawLine(double x1, double y1, double x2, double y2, QColor = Qt::black) override;
	void DrawLine(QPointF const& p1, QPointF const& p2, QColor = Qt::black) override;

	void DrawRect(double x1, double y1, double x2, double y2, QColor = Qt::black) override;
	void DrawRect(QPointF const& p1, QPointF const& p2, QColor = Qt::black) override;

	void DrawEclipse(double x1, double y1, double x2, double y2, QColor = Qt::black) override;
	void DrawEclipse(QPointF const& p1, QPointF const& p2, QColor = Qt::black) override;

	void DrawText(double x1, double y1, double x2, double y2, QString const& sText, QColor = Qt::black) override;
	void DrawText(QPointF const& p1, QPointF const& p2, QString const& sText, QColor = Qt::black) override;
private:
	void PrintGeometry(double x1, double y1, double x2, double y2);

private:
	std::ostream* m_pOutput = nullptr;
};

} // namespace pwpt

#endif // _POWERPOINT_STREAM_PAINTER_HPP_