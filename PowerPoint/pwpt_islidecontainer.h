
#ifndef _POWERPOINT_INTERFACE_ISLIDECONTAINER_HPP_
#define _POWERPOINT_INTERFACE_ISLIDECONTAINER_HPP_

#include <memory>

#include "pwpt_islide.h"

namespace pwpt
{

class ISlideContainer
{
public:
    using size_type = size_t;

    // Capacity
    virtual bool IsEmpty() const = 0;
    virtual size_type Count() const = 0;

    // Modifiers

    // clear all slides
    virtual void Clear() = 0;

    // removes nCount slides from nSlideIndex index
    virtual void Remove(int nSlideIndex, size_type nCount = 1) = 0;

    virtual void Add(ISlide_SPtr) = 0;

    virtual void Insert(ISlide_SPtr, int nIndex) = 0;

    virtual ISlide_SPtr GetSlide(int nIndex) const = 0;

}; // interface ISlideContainer
using ISlideContainer_UPtr = std::unique_ptr<class ISlideContainer>;
using ISlideContainer_SPtr = std::shared_ptr<class ISlideContainer>;
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ISLIDECONTAINER_HPP_
