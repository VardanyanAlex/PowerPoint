
#ifndef _POWERPOINT_COMMAND_HANDLER_HPP_
#define _POWERPOINT_COMMAND_HANDLER_HPP_

#include "pwpt_icommandhandler.h"
#include "commandparser.h"

namespace pwpt
{

class CCommandHandler : public IHandler
{
public:
	CCommandHandler();

	CCommandHandler(CCommandHandler const&) = delete;
	CCommandHandler& operator=(CCommandHandler const&) = delete;


	//void SetEditor(CEditor&) override;

	EState Handle(ICommand_SPtr&) override;

public slots:
	void OnInputDetected(std::string const&) override;
	void OnCommandCreatedAction(IAction_SPtr&) override;

private:
	Command::CParser m_oParser;

};

} // namespace pwpt

#endif // _POWERPOINT_COMMAND_HANDLER_HPP_
