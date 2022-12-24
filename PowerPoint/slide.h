
#ifndef _POWERPOINT_SLIDE_MODEL_HPP_
#define _POWERPOINT_SLIDE_MODEL_HPP_

#include <deque>

#include "pwpt_iobject.h"
#include "pwpt_islide.h"

namespace pwpt
{

class CSlide : public pwpt::ISlide
{
public:
    // Capacity
    bool IsEmpty() const override;
    size_type GetCount() const override;

    // Modifiers

    // clear all objects
    void Clear() override;

    // clear all objects in specified area
    void Clear(QPointF const& pLeftTop, QPointF const& pRightBottom) override;

    //virtual void Remove(std::deque<CObject>::iterator) = 0;

    void Remove(QPointF const& pObjectsCenter) override;

    void Add(IObject_SPtr pObject) override;

    // if input qpoint is in any shape returns it
    IObject_SPtr GetObject(QPointF const&) const override;

    ObjectList GetObjects(QPointF pLeftTop, QPointF pRightBottom) const override;

    std::deque<IObject_SPtr> GetObjects() const override;

private:
	std::deque<IObject_SPtr> m_aObjects;
};

} // namespace pwpt

#endif // _POWERPOINT_SLIDE_MODEL_HPP_
