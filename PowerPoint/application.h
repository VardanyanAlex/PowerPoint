
#ifndef _POWERPOINT_MAIN_APPLICATION_HPP_
#define _POWERPOINT_MAIN_APPLICATION_HPP_

#include <memory>

#include "document.h"
#include "pwpt_icommandhandler.h"
#include "pwpt_icommandline.h"
#include "pwpt_imachine.h"

namespace pwpt
{

namespace App
{

class CApplication
{ // singleton
public:
	CApplication(CApplication const&) = delete;
	CApplication& operator=(CApplication const&) = delete;

	static CApplication& Instance();

	void Run();
	PwPtDoc_SPtr GetDocument() const;

private:
	CApplication();

private:
	ICommandLine_UPtr		m_pConsole = nullptr;
	ICommandHandler_UPtr	m_pCommandHandler = nullptr;
	IMachine_SPtr			m_pActionMachine;

	PwPtDoc_SPtr			m_pDocument;

}; // class CApplication

} // namespace App

} // namespace pwpt

#endif // _POWERPOINT_MAIN_APPLICATION_HPP_
