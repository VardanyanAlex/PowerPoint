
#ifndef _POWERPOINT_MAIN_APPLICATION_HPP_
#define _POWERPOINT_MAIN_APPLICATION_HPP_

#include <memory>

#include "document.h"

namespace App
{

class PwPtApplication
{
public:
	PwPtApplication();
	void Exec();

private:
	void RunCommand(CCommand&&);
	// provide CEditor to CCommand and run it 

private:
	std::unique_ptr<CConsole>		m_pConsole;
	std::unique_ptr<CTaskMachine>	m_pTaskMachine;

private:
	std::unique_ptr<Document::CPwPtDocument>		m_pDocument;

}; // class PwPtApplication

} // namespace App

#endif // _POWERPOINT_MAIN_APPLICATION_HPP_
