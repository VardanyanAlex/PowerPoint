
#include <algorithm>
#include <stdexcept>

#include "slideshow.h"

namespace pwpt
{

bool CSlideShow::IsEmpty() const
{
	return m_aSlides.empty();
}

CSlideShow::size_type CSlideShow::Count() const
{
	return m_aSlides.size();
}

void CSlideShow::Clear()
{
	m_aSlides.clear();
}

void CSlideShow::Remove(int iSlideIndex, size_type nCount)
{
	if (iSlideIndex <= 0)
		throw std::logic_error{ "Invalid indexation!!!\n\n" };

	auto range_begin = m_aSlides.begin();
	auto range_end = m_aSlides.begin();
	std::advance(range_begin, iSlideIndex - 1);
	std::advance(range_end, iSlideIndex + nCount - 1);

	m_aSlides.erase(range_begin, range_end);
}

void CSlideShow::Add(ISlide_SPtr pSlide)
{
	m_aSlides.push_back(pSlide);
}

void CSlideShow::Insert(ISlide_SPtr pSlide, int iIndex)
{
	if (iIndex <= 0)
		throw std::logic_error{ "Invalid indexation!!!\n\n" };

	auto it = m_aSlides.begin();
	std::advance(it, iIndex - 1);

	m_aSlides.insert(it, pSlide);
}

ISlide_SPtr CSlideShow::GetSlide(int iIndex) const
{
	if (iIndex <= 0)
		throw std::logic_error{ "Invalid indexation!!!\n\n" };

	auto it = m_aSlides.begin();
	std::advance(it, iIndex - 1);

	return *it;
}

} // namespace pwpt
