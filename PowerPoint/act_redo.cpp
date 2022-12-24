
#include "act_redo.h"

namespace pwpt
{

void CRedo::Run()
{
	if (m_pRedoStack == nullptr || m_pRedoStack->empty())
		throw CActionExecException{ "For now <redo> action cannot be used" };

	auto pAction = m_pRedoStack->top();
	m_pRedoStack->pop();

	auto pReverseAction = pAction->Reverse();

	if (pReverseAction->CanRun())
	{
		pReverseAction->Run();

		m_pUndoStack->push(pReverseAction);
	}
	else
		throw CActionExecException{ "Unexpected error occurred!!!" };
}

bool CRedo::CanRun() const
{
	return m_pRedoStack != nullptr && !m_pRedoStack->empty() &&
		   m_pUndoStack != nullptr;
}

IAction_SPtr CRedo::Reverse() const
{
	throw CActionExecException{ "Be Carefull, please!. You can't reverse <redo> action" };
}

void CRedo::ProvideUndoRedoStacks(std::stack<IAction_SPtr>* pUndoStack, std::stack<IAction_SPtr>* pRedoStack)
{
	m_pUndoStack = pUndoStack;
	m_pRedoStack = pRedoStack;
}

}
