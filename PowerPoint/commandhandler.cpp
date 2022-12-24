
#include "pwpt_appmanager.h"
#include "commandhandler.h"
#include "streampainter.h"

namespace pwpt
{

CCommandHandler::CCommandHandler()
{}

EState CCommandHandler::Handle(ICommand_SPtr& pCommand)
{
	EState eCommandExecStatus = EState::success;

	QObject::connect(pCommand.get(),  &Command::ICommand::CreatedAction, this, &IHandler::OnCommandCreatedAction);

	try
	{
		pCommand->Execute();
	}
	catch (std::exception const& ex) 
	{
		std::ostream* pOutput = App::CAppManager::AppInstance().GetOutputStreamDevice();
		*pOutput << ex.what();

		eCommandExecStatus = EState::failure;
	}

	return eCommandExecStatus;
}

void CCommandHandler::OnInputDetected(std::string const& sInput)
{
	std::stringstream sInputStream{ sInput };

	ICommand_SPtr pCmd = nullptr;
	std::ostream* pOutput = App::CAppManager::AppInstance().GetOutputStreamDevice();
	
	try
	{
		pCmd = m_oParser.Parse(sInputStream);

		EState eCommandExecStatus = Handle(pCmd);

		if (eCommandExecStatus == EState::success)
			*pOutput << "--> Command executed successfully\n\n";
		else
			*pOutput << "--> Failed to execute command\n\n";
	}
	catch (std::exception const& ex)
	{
		*pOutput << ex.what();
	}
}

void CCommandHandler::OnCommandCreatedAction(IAction_SPtr& pAction)
{
	emit ActionConstructed(pAction);
}

}
