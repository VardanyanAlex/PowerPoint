
#ifndef _POWERPOINT_TASK_ENGINES_HPP_
#define _POWERPOINT_TASK_ENGINES_HPP_

#include "task.h"

class CTaskFactory
{ // singleton
public:
	CTaskFactory const& Instance();
	ITask* CreateTask(CMaterial&&);

private:
	CTaskFactory();

};

#endif // _POWERPOINT_TASK_ENGINES_HPP_
