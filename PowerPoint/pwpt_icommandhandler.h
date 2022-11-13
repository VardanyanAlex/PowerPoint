
#ifndef _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_
#define _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_

#include <memory>

#include <QObject>

#include "pwpt_icommand.h"
#include "pwpt_idoceditor.h"

namespace pwpt
{

using ICommandHandler_Ptr = std::unique_ptr<class IHandler>; 

enum class EState
{
	success,
	failure
};

class IHandler : public QObject
{
	Q_OBJECT

public:
	virtual void SetEditor(IDocEditor_Ptr) = 0;
	
	virtual EState Handle(ICommand_Ptr&) = 0;

//signals:
	//virtual void actionConstructed(IACtion_Ptr) = 0;

public slots:
	virtual void OnCommandConstructed(ICommand_Ptr) = 0;
	//(
	//	[](ICommand_Ptr pCommand) )
	//	{
	//	//std::cout << "We received: " << input << std::endl;
	//	}
	//);

}; // interface IMachine

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_COMMAND_HANDLER_HPP_
