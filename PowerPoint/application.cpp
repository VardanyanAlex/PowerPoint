
#include "application.h"
#include "commandhandler.h"
#include "commandline.h"

namespace pwpt
{

namespace App
{

CApplication::CApplication()
{
	m_pConsole = ICommandLine_UPtr(new CCommandLine);
	m_pCommandHandler = ICommandHandler_UPtr(new CCommandHandler);

	QObject::connect(m_pConsole.get(), SIGNAL(InputDetected(std::string const&)),
		m_pCommandHandler.get(), SLOT(OnInputDetected(std::string const&)));
}

CApplication& CApplication::Instance()
{ // Meyers' singleton
	static CApplication oApp;

	return oApp;
}

void CApplication::Run()
{
	m_pConsole->Run();
	
}

PwPtDoc_SPtr CApplication::GetDocument() const
{
	return m_pDocument;
}

} // namespace App

} // namespace pwpt
