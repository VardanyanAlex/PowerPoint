
#ifndef _POWERPOINT_INTERFACE_ACTION_HPP_
#define _POWERPOINT_INTERFACE_ACTION_HPP_

#include <memory>

#include "pwpt_idocument.h"

namespace pwpt
{

class IAction 
{
public:
	virtual void Run() = 0;

	void SetDocument(PwPtDoc_SPtr&);
	
protected:
	void CheckDocumentValidity() const;

protected:
	PwPtDoc_SPtr m_pDoc = nullptr;

};
using IAction_SPtr = std::shared_ptr<IAction>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ACTION_HPP_
