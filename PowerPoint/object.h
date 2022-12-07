
#ifndef _POWERPOINT_OBJECT_HPP_
#define _POWERPOINT_OBJECT_HPP_

#include "pwpt_iobject.h"

namespace pwpt
{

class CObject : public IObject
{
public:
	QPointF GetCenter() const override;
	QPair<QPointF, QPointF> GetGeometry() const override;
	EShape GetShape() const override;
	QColor GetColor() const override;

	void SetCenter(QPointF const&) override;
	void SetGeometry(QPointF const&, QPointF const&) override;
	void SetShape(EShape const&) override;
	void SetColor(QColor const&) override;

private:
	QPointF m_oCenter;
	EShape m_eShape;
	QColor m_oColor;

	QPointF m_oLeftTopPos;
	QPointF m_oRightBottomPos;
};

} // namespace pwpt

#endif // !_POWERPOINT_OBJECT_HPP_
