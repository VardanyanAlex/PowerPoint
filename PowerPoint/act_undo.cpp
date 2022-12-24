
#include "act_undo.h"

namespace pwpt
{

void CUndo::Run()
{
	if (m_pUndoStack->empty())
		throw CActionExecException{ "For now <undo> action cannot be used" };

	auto pAction = m_pUndoStack->top();
	m_pUndoStack->pop();

	auto pReverseAction = pAction->Reverse();

	if (pReverseAction->CanRun())
	{
		pReverseAction->Run();

		m_pRedoStack->push(pReverseAction);
	}
	else
		throw CActionExecException{ "Unexpected error occurred!!!" };
}

bool CUndo::CanRun() const
{
	return m_pUndoStack != nullptr && !m_pUndoStack->empty() &&
		   m_pRedoStack != nullptr;
}

IAction_SPtr CUndo::Reverse() const
{
	throw CActionExecException{ "Be Carefull, please!. You can't reverse <undo> action" };
}

void CUndo::ProvideUndoRedoStacks(std::stack<IAction_SPtr>* pUndoStack, std::stack<IAction_SPtr>* pRedoStack)
{
	m_pUndoStack = pUndoStack;
	m_pRedoStack = pRedoStack;
}

}
