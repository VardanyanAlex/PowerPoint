
#ifndef _POWERPOINT_DOCUMENT_EDITOR_HPP_
#define _POWERPOINT_DOCUMENT_EDITOR_HPP_

#include <iostream>
#include <memory>
#include <stack>

#include "pwpt_imachine.h"

namespace pwpt
{

class CMachine : public IMachine
{
public:
	void Do(IAction_SPtr const&);

private:
	void SendToRedoStack(IAction_SPtr const&);
	void SendToUndoStack(IAction_SPtr const&);

	void RemoveUnnecessaryActions();

private:
	std::stack<IAction_SPtr> m_aDoneActions;
	std::stack<IAction_SPtr> m_aUndoedActions;
};

} // namespace pwpt

#endif // _POWERPOINT_DOCUMENT_EDITOR_HPP_
