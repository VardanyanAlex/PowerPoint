
#ifndef _POWERPOINT_INTERFACE_SLIDE_HPP_
#define _POWERPOINT_INTERFACE_SLIDE_HPP_

#include "pwpt_iobject.h"

namespace pwpt
{

class ISlide
{
public:
    using size_type     = size_t;

    // Capacity
    virtual bool IsEmpty() const = 0;
    virtual size_type GetCount() const = 0;

    // Modifiers
    
    // clear all objects
    virtual void Clear() = 0;

    // clear all objects in specified area
    virtual void Clear(QPointF const& pLeftTop, QPointF const& pRightBottom) = 0;

    //virtual void Remove(std::deque<CObject>::iterator) = 0;

    virtual void Remove(QPointF const& pObjectsCenter) = 0;

    virtual void Add(IObject_SPtr oObject) = 0;

    // if input qpoint is in any shape returns it
    virtual IObject_SPtr GetObject(QPointF const&) const = 0;

    // return objects group in area from leftTop to rightBottom
    virtual ObjectList GetObjects(QPointF pLeftTop, QPointF pRightBottom) const = 0;
    
    virtual ObjectList GetObjects() const = 0;

}; // interface ISlide
using ISlide_UPtr = std::unique_ptr<class ISlide>;
using ISlide_SPtr = std::shared_ptr<class ISlide>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_SLIDE_HPP_
