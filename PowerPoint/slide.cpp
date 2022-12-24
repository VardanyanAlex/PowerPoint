
#include "slide.h"

namespace pwpt
{

// Capacity
bool CSlide::IsEmpty() const 
{
	return m_aObjects.empty();
}

CSlide::size_type CSlide::GetCount() const
{
	return m_aObjects.size();
}

void CSlide::Clear()
{
	m_aObjects.clear();
}

void CSlide::Clear(QPointF const& pLeftTop, QPointF const& pRightBottom)
{
	for (auto const& pObject : m_aObjects)
	{
		auto oGeometry = pObject->GetGeometry();

		if (oGeometry.first.x() >= pLeftTop.x() && oGeometry.first.y() >= pLeftTop.y() &&
			oGeometry.second.x() <= pRightBottom.x() && oGeometry.second.y() <= pRightBottom.y())
		{
			m_aObjects.erase(std::remove(m_aObjects.begin(), m_aObjects.end(), pObject));
		}
	}
}

void CSlide::Remove(QPointF const& pObjectsCenter)
{
	for (auto const& pObject : m_aObjects)
	{
		if (pObject->GetCenter() == pObjectsCenter)
		{
			m_aObjects.erase(std::remove(m_aObjects.begin(), m_aObjects.end(), pObject));
		}
	}
}

void CSlide::Add(IObject_SPtr pObject)
{
	m_aObjects.push_back(pObject);
}

IObject_SPtr CSlide::GetObject(QPointF const& pObjectsCenter) const
{
	IObject_SPtr pNeededObject = nullptr;

	for (auto const& pObject : m_aObjects)
	{
		if (pObject->GetCenter() == pObjectsCenter)
		{
			pNeededObject = pObject;
			break;
		}
	}

	return pNeededObject;
}

ObjectList CSlide::GetObjects(QPointF pLeftTop, QPointF pRightBottom) const
{
	ObjectList aViableObjects{};

	for (auto const& pObject : m_aObjects)
	{
		auto oGeometry = pObject->GetGeometry();

		if (oGeometry.first.x() >= pLeftTop.x() && oGeometry.first.y() >= pLeftTop.y() &&
			oGeometry.second.x() <= pRightBottom.x() && oGeometry.second.y() <= pRightBottom.y())
		{
			aViableObjects.push_back(pObject);
		}
	}

	return aViableObjects;
}

ObjectList CSlide::GetObjects() const
{
	return m_aObjects;
}

} // namespace pwpt
