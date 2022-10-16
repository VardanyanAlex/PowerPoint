
#ifndef _POWERPOINT_INTERFACE_SLIDE_HPP_
#define _POWERPOINT_INTERFACE_SLIDE_HPP_

#include <memory>

namespace pwpt
{

using Slide_Ptr = std::unique_ptr<ISlide>;
using Slide_SharedPtr = std::shared_ptr<ISlide>;

class ISlide
{
public:
    using size_type     = size_t;

    // Capacity
    virtual bool Empty() = 0;
    virtual size_type Count() = 0;

    // Modifiers
    
    // clear all objects
    virtual void Clear() = 0;

    // clear all objects in specified area
    virtual void Clear(QPointF pLeftTop, QPointF pRightBottom) = 0;

    virtual void Remove(Iterator) = 0;

    virtual void Remove(QPointF pObjectsCenter) = 0;

    virtual void Add(CObject&& oObject, QPointF pLeftTop = CSlidesCenter) = 0;

    // if input qpoint is in any shape returns it
    virtual CObject& GetObject(QPointF) = 0;

    // return objects group in area from leftTop to rightBottom
    virtual CObjectsGroup GetObjects(QPointF pLeftTop, QPointF pRightBottom) = 0;

} // interface ISlide

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_SLIDE_HPP_
