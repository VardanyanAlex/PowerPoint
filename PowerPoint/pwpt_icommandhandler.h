
#ifndef _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_
#define _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_

#include <memory>

#include <QObject>

#include "pwpt_iaction.h"
#include "pwpt_icommand.h"

namespace pwpt
{

enum class EState
{
	success,
	failure
};

class IHandler : public QObject
{
	Q_OBJECT

public:
	virtual EState Handle(ICommand_SPtr&) = 0;

signals:
	void ActionConstructed(IAction_SPtr&);

public slots:
	virtual void OnInputDetected(std::string const&) = 0;
	virtual void OnCommandCreatedAction(IAction_SPtr&) = 0;

}; // interface IHandler
using ICommandHandler_UPtr = std::unique_ptr<class IHandler>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_
