
#ifndef _POWERPOINT_INTERFACE_MACHINE_HPP_
#define _POWERPOINT_INTERFACE_MACHINE_HPP_

#include <memory>

namespace pwpt
{

class IMachine
{
public:

	//virtual void Run(IACtion_Ptr) = 0;

	//virtual void AddAction(IACtion_Ptr) = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual void RemoveUnnecessaryActions() = 0;

public /*slots*/:
	//virtual void onActionConstructed(IACtion_Ptr) = 0;

}; // interface IMachine
using IMachine_ptr = std::unique_ptr<class IMachine>;
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_MACHINE_HPP_
