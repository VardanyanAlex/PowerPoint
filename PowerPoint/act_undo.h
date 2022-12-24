
#ifndef _POWERPOINT_ACTION_UNDO_HPP_
#define _POWERPOINT_ACTION_UNDO_HPP_

#include <stack>

#include "pwpt_iaction.h"
#include "pwpt_islidecontainer.h"

namespace pwpt
{

class CUndo : public IAction 
{
public:
	CUndo() =default;

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

#endif // _POWERPOINT_ACTION_UNDO_HPP_
