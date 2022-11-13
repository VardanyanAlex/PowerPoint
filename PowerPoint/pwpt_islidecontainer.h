
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
    virtual bool Empty() = 0;
    virtual size_type Count() = 0;

    // Modifiers

    // clear all slides
    virtual void Clear() = 0;

    // removes nCount slides from nSlideIndex index
    virtual void Remove(unsigned nSlideIndex, size_type nCount = 1) = 0;

    virtual void Add(Slide_Ptr) = 0;

    virtual void Insert(Slide_Ptr, unsigned nIndex) = 0;

    virtual Slide_SharedPtr& GetSlide(unsigned nIndex) = 0;

}; // interface ISlideContainer
using SlideContainer_Ptr = std::unique_ptr<class ISlideContainer>;
using SlideContainer_SharedPtr = std::shared_ptr<class ISlideContainer>;
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ISLIDECONTAINER_HPP_
