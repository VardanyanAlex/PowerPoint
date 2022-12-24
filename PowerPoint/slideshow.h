
#ifndef _POWERPOINT_SLIDESHOW_MODEL_HPP
#define _POWERPOINT_SLIDESHOW_MODEL_HPP

#include <list>

#include "pwpt_islide.h"
#include "pwpt_islidecontainer.h"

namespace pwpt
{

class CSlideShow : public pwpt::ISlideContainer
{
public:
    using size_type = size_t;

    CSlideShow() = default;

    CSlideShow(CSlideShow const&) =delete;
    CSlideShow& operator=(CSlideShow) =delete;

    CSlideShow(CSlideShow&&) =delete;
    CSlideShow& operator=(CSlideShow&&) =delete;

    // Capacity
    bool IsEmpty() const override;
    size_type Count() const override;

    // Modifiers

    // clear all slides
    void Clear() override;

    // removes nCount slides from nSlideIndex index
    void Remove(int nSlideIndex, size_type nCount = 1) override;

    void Add(ISlide_SPtr) override;

    void Insert(ISlide_SPtr, int nIndex) override;

    ISlide_SPtr GetSlide(int nIndex) const override;

private:
    std::list<ISlide_SPtr> m_aSlides;
};

} // namespace pwpt

#endif // _POWERPOINT_SLIDESHOW_MODEL_HPP
