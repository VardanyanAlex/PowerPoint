
#include "pwpt_iaction.h"
#include "pwpt_islidecontainer.h"

namespace pwpt
{

class CAddSlide : public IAction 
{
public:
	explicit CAddSlide(int iPositionInSlideshow = 0);

	void Run() override;
	bool CanRun() const override;

	IAction_SPtr Reverse() const override;

private:
	ISlide_SPtr						m_pSlide		= nullptr;
	ISlideContainer_SPtr mutable	m_pSlideshow	= nullptr;

	int			m_iNewSlideIndex;
};

} // namespace pwpt
