
#include "application.h"
#include "commandhandler.h"
#include "commandline.h"

namespace pwpt
{

namespace App
{

PwPtApplication::PwPtApplication()
	//: m_pConsole{ std::make_unique<CCommandLine>(new CCommandLine{}) }
{
	m_pConsole = std::unique_ptr<ICommandLine>(new CCommandLine);
	m_pCommandHandler = std::unique_ptr<IHandler>(new CCommandHandler);

	m_pConsole->sigCommandConstructed.connect(m_pCommandHandler->OnCommandConstructed);
}

void PwPtApplication::Exec()
{
	ICommand_Ptr p = nullptr;
	m_pConsole->sigCommandConstructed.emit(std::move(p));
}

} // namespace App

} // namespace pwpt
