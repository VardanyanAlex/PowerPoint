
#ifndef _POWERPOINT_MAIN_APPLICATION_HPP_
#define _POWERPOINT_MAIN_APPLICATION_HPP_

#include <memory>

#include "document.h"
#include "pwpt_icommandhandler.h"
#include "pwpt_icommandline.h"
#include "pwpt_itaskmachine.h"

namespace pwpt
{

namespace App
{

class PwPtApplication
{
public:
	PwPtApplication();
	void Exec();

private:
	ICommandLine_Ptr		m_pConsole = nullptr;
	ICommandHandler_Ptr		m_pCommandHandler = nullptr;
	//IMachine_ptr			m_pActionMachine;

private:
	Document::CPwPtDocument		m_oDocument;

}; // class PwPtApplication

} // namespace App

} // namespace pwpt

#endif // _POWERPOINT_MAIN_APPLICATION_HPP_
