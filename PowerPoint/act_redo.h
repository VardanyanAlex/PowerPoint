
#ifndef _POWERPOINT_ACTION_REDO_HPP_
#define _POWERPOINT_ACTION_REDO_HPP_

#include <stack>

#include "pwpt_iaction.h"
#include "pwpt_islidecontainer.h"

namespace pwpt
{

class CRedo : public IAction
{
public:
	CRedo() =default;

	void Run() override;
	bool CanRun() const override;

	IAction_SPtr Reverse() const override;

	// Own interface
	void ProvideUndoRedoStacks(std::stack<IAction_SPtr>* pUndoStack, std::stack<IAction_SPtr>* pRedoStack);

private:
	std::stack<IAction_SPtr>* m_pUndoStack = nullptr;
	std::stack<IAction_SPtr>* m_pRedoStack = nullptr;
};

} // namespace pwpt

#endif // _POWERPOINT_ACTION_REDO_HPP_
