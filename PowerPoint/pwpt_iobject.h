
#ifndef _POWERPOINT_INTERFACE_IOBJECT_HPP_
#define _POWERPOINT_INTERFACE_IOBJECT_HPP_

#include <deque>
#include <memory>

#include <QColor>
#include <QPair>
#include <QPointF>

#include "shape.h"

namespace pwpt
{

class IObject
{
public:
	virtual QPointF GetCenter() const = 0;
	virtual QPair<QPointF, QPointF> GetGeometry() const = 0;
	virtual CShape GetShape() const = 0;
	virtual QColor GetColor() const = 0;

	virtual void SetCenter(QPointF const&) = 0;
	virtual void SetGeometry(QPointF const&, QPointF const&) = 0;
	virtual void SetShape(CShape const&) = 0;
	virtual void SetColor(QColor const&) = 0;
};
using IObject_SPtr = std::shared_ptr<class IObject>;
using ObjectList = std::deque<std::shared_ptr<class IObject>>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_IOBJECT_HPP_
