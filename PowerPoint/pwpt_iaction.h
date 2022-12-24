
#ifndef _POWERPOINT_INTERFACE_ACTION_HPP_
#define _POWERPOINT_INTERFACE_ACTION_HPP_

#include <exception>
#include <memory>
#include <string>

namespace pwpt
{

class IAction;
using IAction_SPtr = std::shared_ptr<class IAction>;

class IAction 
{
public:
	virtual void Run() = 0;
	virtual bool CanRun() const = 0;

	virtual IAction_SPtr Reverse() const = 0;
};

class CActionExecException : public std::exception
{
public:
	CActionExecException(std::string const&);

	const char* what() const noexcept override;

private:
	std::string m_sErrorMessage;
};

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ACTION_HPP_
