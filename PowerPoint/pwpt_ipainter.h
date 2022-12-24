
#ifndef _POWERPOINT_INTERFACE_PAINTER_HPP_
#define _POWERPOINT_INTERFACE_PAINTER_HPP_

#include <exception>

#include <QColor>
#include <QPainter>
#include <QPointF>

#include "shape.h"

namespace pwpt
{

class IPainter
{
public:
	virtual void Draw(CShape const&, double x1, double y1, double x2, double y2, QColor = Qt::black) = 0;
	virtual void Draw(CShape const&, QPointF const& p1, QPointF const& p2, QColor = Qt::black) = 0;

	virtual void DrawLine(double x1, double y1, double x2, double y2, QColor = Qt::black) = 0;
	virtual void DrawLine(QPointF const& p1, QPointF const& p2, QColor = Qt::black) = 0;

	virtual void DrawRect(double x1, double y1, double x2, double y2, QColor = Qt::black) = 0;
	virtual void DrawRect(QPointF const& p1, QPointF const& p2, QColor = Qt::black) = 0;

	virtual void DrawEclipse(double x1, double y1, double x2, double y2, QColor = Qt::black) = 0;
	virtual void DrawEclipse(QPointF const& p1, QPointF const& p2, QColor = Qt::black) = 0;

	virtual void DrawText(double x1, double y1, double x2, double y2, QString const& sText, QColor = Qt::black) = 0;
	virtual void DrawText(QPointF const& p1, QPointF const& p2, QString const& sText, QColor = Qt::black) = 0;
};

class CUnavailableOutputDevice : public std::exception
{
public:
	CUnavailableOutputDevice(std::string const& sErrorMessage);

	const char* what() const noexcept override;

private:
	std::string m_sErrorMessage;
};

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_PAINTER_HPP_
