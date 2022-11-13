
#ifndef _POWERPOINT_TASK_MACHINE_HPP
#define _POWERPOINT_TASK_MACHINE_HPP

#include "pwpt_itaskmachine.h"

class CActionMachine : public pwpt::IMachine
{
public:
	void SetEditor(CEditor&) override;

	void Run(IACtion_Ptr) override;

	void AddAction(IACtion_Ptr) override;
	void Undo() override;
	void Redo() override;
	void RemoveUnnecessaryActions() override;

public /*slots*/:
	virtual void onActionConstructed(IACtion_Ptr) = 0;

private:
	//CActionsStack +
	//CActionsStack -

	//std::shared_ptr<CEditor>
};

#endif // _POWERPOINT_TASK_MACHINE_HPP
