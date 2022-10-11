
#ifndef _POWERPOINT_SLIDE_MODEL_HPP_
#define _POWERPOINT_SLIDE_MODEL_HPP_

#include <deque>

class CSlide
{
public:
    using size_type     = size_t;

    CSlide() = default;

    ~CSlide();

    CSlide(CSlide const&);
    CSlide& operator=(CSlide);

    CSlide(CSlide&&) noexcept;
    CSlide& operator=(CSlide&&) noexcept;

    // Capacity
    bool Empty();
    size_type Count();

    // Modifiers
    
    // clear all objects
    void Clear();

    // clear all objects in specified area
    void Clear(QPointF pLeftTop, QPointF pRightBottom);

    void Remove(Iterator);

    void Remove(QPointF pObjectsCenter);

    void Add(CObject&& oObject, QPointF pLeftTop = CSlidesCenter);

    // if input qpoint is in any shape returns it
    CObject& GetObject(QPointF);

    // return objects group in area from leftTop to rightBottom
    CObjectsGroup GetObjects(QPointF pLeftTop, QPointF pRightBottom);

private:
	std::deque<CObject> m_aObjects;
};

#endif // _POWERPOINT_SLIDE_MODEL_HPP_
