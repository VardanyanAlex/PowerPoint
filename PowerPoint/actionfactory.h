
#ifndef _POWERPOINT_ACTION_FACTORY_HPP_
#define _POWERPOINT_ACTION_FACTORY_HPP_

#include "pwpt_iaction.h"

namespace pwpt
{

class CActionFactory
{
public:
	CActionFactory(CActionFactory const&) = delete;
	CActionFactory& operator=(CActionFactory const&) = delete;

	static CActionFactory& GetInstance();

	IAction_SPtr CreateAction(ICommand_SPtr const&) const;

private:
	CActionFactory() =default;

};

} // namespace pwpt

#endif // _POWERPOINT_ACTION_FACTORY_HPP_
