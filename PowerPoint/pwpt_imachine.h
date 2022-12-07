
#ifndef _POWERPOINT_INTERFACE_IMACHINE_HPP_
#define _POWERPOINT_INTERFACE_IMACHINE_HPP_

#include <iostream>
#include <memory>

#include "pwpt_iaction.h"

namespace pwpt
{

class IMachine
{
public:
	virtual void Do(IAction_SPtr const&) = 0;

private:
	virtual void SendToUndoStack(IAction_SPtr const&) = 0;
	virtual void SendToRedoStack(IAction_SPtr const&) = 0;

	virtual void RemoveUnnecessaryActions() = 0;

};
using IMachine_SPtr = std::shared_ptr<class IMachine>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_IDOCUMENT_EDITOR_HPP_
