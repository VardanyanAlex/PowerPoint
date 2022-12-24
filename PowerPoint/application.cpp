
#include "actionmachine.h"
#include "application.h"
#include "commandhandler.h"
#include "commandline.h"
#include "document.h"

namespace pwpt
{

namespace App
{

CPowerpointApp::CPowerpointApp()
{
	// CApp components
	m_pDocument = std::make_shared<pwpt::Document::CPwPtDocument>();

	// own components
	m_pConsole = std::make_unique<CCommandLine>();
	m_pCommandHandler = std::make_unique<CCommandHandler>();
	m_pActionMachine = std::make_unique<CActionMachine>();

	QObject::connect(m_pConsole.get(), SIGNAL(InputDetected(std::string const&)),
		m_pCommandHandler.get(), SLOT(OnInputDetected(std::string const&)));

	QObject::connect(m_pCommandHandler.get(), SIGNAL(ActionConstructed(IAction_SPtr&)), m_pActionMachine.get(), SLOT(onActionCreated(IAction_SPtr&)));
}

void CPowerpointApp::Run()
{
	m_pConsole->Run();
}

} // namespace App

} // namespace pwpt
