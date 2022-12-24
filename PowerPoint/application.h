
#ifndef _POWERPOINT_MAIN_APPLICATION_HPP_
#define _POWERPOINT_MAIN_APPLICATION_HPP_

#include <memory>

#include "pwpt_app.h"
#include "pwpt_icommandhandler.h"
#include "pwpt_icommandline.h"
#include "pwpt_imachine.h"

namespace pwpt
{

namespace App
{

class CPowerpointApp : public CApp
{ // singleton
public:
	CPowerpointApp();
	CPowerpointApp(CPowerpointApp const&) = delete;
	CPowerpointApp& operator=(CPowerpointApp const&) = delete;

	// CApp interface
	void Run() override;

private:
	ICommandLine_UPtr		m_pConsole = nullptr;
	ICommandHandler_UPtr	m_pCommandHandler = nullptr;
	IMachine_UPtr			m_pActionMachine;

}; // class CPowerpointApp

} // namespace App

} // namespace pwpt

#endif // _POWERPOINT_MAIN_APPLICATION_HPP_
