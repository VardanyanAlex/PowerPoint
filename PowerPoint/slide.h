
#ifndef _POWERPOINT_SLIDE_MODEL_HPP_
#define _POWERPOINT_SLIDE_MODEL_HPP_

#include <deque>

#include "pwpt_islide.h"

class CSlide : public pwpt::ISlide
{
public:

    CSlide() = default;

    ~CSlide();

    CSlide(CSlide const&);
    CSlide& operator=(CSlide);

    CSlide(CSlide&&) noexcept;
    CSlide& operator=(CSlide&&) noexcept;

    // Capacity
    bool IsEmpty() const override;
    size_type GetCount() const override;

    // Modifiers

    // clear all objects
    void Clear() override;

    // clear all objects in specified area
    void Clear(QPointF pLeftTop, QPointF pRightBottom) override;

    void Remove(std::deque<CObject>::iterator) override;

    void Remove(QPointF pObjectsCenter) override;

    void Add(CObject&& oObject, QPointF pLeftTop = CSlidesCenter) override;

    // if input qpoint is in any shape returns it
    CObject& GetObject(QPointF) override;

    // return objects group in area from leftTop to rightBottom
    CObjectsGroup GetObjects(QPointF pLeftTop, QPointF pRightBottom) override;

private:
	std::deque<CObject> m_aObjects;
};

#endif // _POWERPOINT_SLIDE_MODEL_HPP_
