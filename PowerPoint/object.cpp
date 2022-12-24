
#include "object.h"

namespace pwpt
{

QPointF CObject::GetCenter() const
{
	return m_oCenter;
}

QPair<QPointF, QPointF> CObject::GetGeometry() const 
{
	return QPair<QPointF, QPointF>{m_oLeftTopPos, m_oRightBottomPos};
}

CShape CObject::GetShape() const
{
	return m_eShape;
}

QColor CObject::GetColor() const 
{
	return m_oColor;
}

void CObject::SetCenter(QPointF const& oCenter) 
{
	double PartLenOnX = m_oCenter.x() - m_oLeftTopPos.x();
	double PartLenOnY = m_oCenter.y() - m_oLeftTopPos.y();

	m_oCenter = oCenter;

	m_oLeftTopPos.setX(m_oCenter.x() - PartLenOnX);
	m_oLeftTopPos.setY(m_oCenter.y() + PartLenOnY);

	m_oRightBottomPos.setX(m_oCenter.x() + PartLenOnX);
	m_oRightBottomPos.setY(m_oCenter.y() - PartLenOnY);
}

void CObject::SetGeometry(QPointF const& oLeftTop, QPointF const& oRightBottom) 
{
	m_oLeftTopPos = oLeftTop;
	m_oRightBottomPos = oRightBottom;

	m_oCenter.setX((m_oLeftTopPos.x() + m_oRightBottomPos.x()) / 2);
	m_oCenter.setY((m_oLeftTopPos.y() + m_oRightBottomPos.y()) / 2);
}

void CObject::SetShape(CShape const& eShape)
{
	m_eShape = eShape;
}

void CObject::SetColor(QColor const& oColor) 
{
	m_oColor = oColor;
}

} // namespace pwpt
