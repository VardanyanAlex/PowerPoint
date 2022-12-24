
#ifndef _POWERPOINT_DOCUMENT_EDITOR_HPP_
#define _POWERPOINT_DOCUMENT_EDITOR_HPP_

#include <iostream>
#include <memory>
#include <stack>

#include "pwpt_imachine.h"

namespace pwpt
{

class CActionMachine : public IMachine
{
public:
	void Do(IAction_SPtr&) override;

public slots:
	void onActionCreated(IAction_SPtr&) override;

private:
	void SendToRedoStack(IAction_SPtr const&);
	void SendToUndoStack(IAction_SPtr const&);

private:
	std::stack<IAction_SPtr> m_aForUndoActions;
	std::stack<IAction_SPtr> m_aForRedoActions;
};

} // namespace pwpt

#endif // _POWERPOINT_DOCUMENT_EDITOR_HPP_
