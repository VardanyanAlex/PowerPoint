
#include "act_redo.h"
#include "act_undo.h"
#include "actionmachine.h"

namespace pwpt
{

void CActionMachine::Do(IAction_SPtr& pAction)
{
	if (pAction->CanRun())
	{
		pAction->Run();
	}
}

void CActionMachine::onActionCreated(IAction_SPtr& pAction)
{
	auto pUndo = std::dynamic_pointer_cast<CUndo>(pAction);
	auto pRedo = std::dynamic_pointer_cast<CRedo>(pAction);

	if (pUndo != nullptr)
	{
		pUndo->ProvideUndoRedoStacks(&m_aForUndoActions, &m_aForRedoActions);

		if (pUndo->CanRun())
		{
			pUndo->Run();
		}
	}
	else if (pRedo != nullptr)
	{
		pRedo->ProvideUndoRedoStacks(&m_aForUndoActions, &m_aForRedoActions);

		if (pRedo->CanRun())
		{
			pRedo->Run();
		}
	}
	else
	{
		Do(pAction);

		SendToUndoStack(pAction);
	}
}

void CActionMachine::SendToUndoStack(IAction_SPtr const& pAction)
{
	m_aForUndoActions.push(pAction);
}

void CActionMachine::SendToRedoStack(IAction_SPtr const& pAction)
{
	m_aForRedoActions.push(pAction);
}

} // namespace pwpt
