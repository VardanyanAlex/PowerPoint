
#ifndef _POWERPOINT_SLIDESHOW_MODEL_HPP
#define _POWERPOINT_SLIDESHOW_MODEL_HPP

#include <list>

#include "pwpt_islidecontainer.h"

class CSlideShow : public pwpt::ISlideContainer
{
public:
    using size_type = size_t;

    CSlideShow() = default;

    ~CSlideShow();

    CSlideShow(CSlideShow const&) =delete;
    CSlideShow& operator=(CSlideShow) =delete;

    CSlideShow(CSlideShow&&) =delete;
    CSlideShow& operator=(CSlideShow&&) =delete;

    // Capacity
    bool Empty();
    size_type Count();

    // Modifiers

    // clear all slides
    void Clear();

    // removes nCount slides from nSlideIndex index
    void Remove(unsigned nSlideIndex, size_type nCount = 1);

    void Add(CSlide&&);

    void Insert(CSlide&&, unsigned nIndex);

    CSlide& GetSlide(unsigned nIndex);

private:
    std::list<CSlide> m_aSlides;
};

#endif // _POWERPOINT_SLIDESHOW_MODEL_HPP
