
#include "pwpt_iaction.h"
#include "pwpt_islide.h"
#include "pwpt_islidecontainer.h"

namespace pwpt
{

class CDeleteSlide : public IAction 
{
public:
	explicit CDeleteSlide(int iPositionInSlideshow = 0);

	// IAction interface impl
	void Run() override;
	bool CanRun() const override;

	IAction_SPtr Reverse() const override;

	// Own interface
	void SetWorkingSlideshow(ISlideContainer_SPtr);

private:
	ISlide_SPtr						m_pSlide		= nullptr;
	ISlideContainer_SPtr mutable	m_pSlideshow	= nullptr;

	int						m_iPositionInSlideshow;
};

} // namespace pwpt
