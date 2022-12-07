
#include "actionfactory.h"
#include "commandhandler.h"

namespace pwpt
{

CCommandHandler::CCommandHandler()
{}

EState CCommandHandler::Handle(ICommand_SPtr& pCommand)
{
	//CActionFactory& oFactory = CActionFactory::GetInstance();

	pCommand->Execute()

	//IAction_SPtr pAction = oFactory.CreateAction(pCommand);

	return EState::success;
}

void CCommandHandler::OnInputDetected(std::string const& sInput)
{
	std::stringstream sInputStream{ sInput };
	ICommand_SPtr oCmd = m_oParser.Parse(sInputStream);

	Handle(oCmd);
}

}
