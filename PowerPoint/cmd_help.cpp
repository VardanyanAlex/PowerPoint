
#include <fstream>
#include <string>
#include <windows.h>   // WinApi header

#include "cmd_help.h"
#include "pwpt_appmanager.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 

CHelpCmd::CHelpCmd()
{}

void CHelpCmd::Execute()
{
	auto& oApp = App::CAppManager::AppInstance();

	PwPtDoc_SPtr pDoc = App::CAppManager::AppInstance().GetDocument();
	if (pDoc == nullptr)
		throw CCmdExecException{ "Application's document is invalid" };

	std::ostream* pOutput =  oApp.GetOutputStreamDevice();
	
	std::string sHelpFilePath = "../HELP.txt";

	SetConsoleOutputCP(CP_UTF8);
	*pOutput << std::ifstream(sHelpFilePath).rdbuf();

}

ICommand_SPtr CHelpCmd::Clone() const
{
	return std::make_shared<CHelpCmd>(*this);
}

bool CHelpCmd::MainOptionRequired() const
{
	return false;
}

size_t CHelpCmd::RequiredMinOptionsCount() const
{
	return 0;
}

bool CHelpCmd::Acceptarg(std::string const& sOption, std::any oValue)
{
	return false;
}

bool CHelpCmd::Validate() const
{
	return true;
}

} // namespace Command

} // namespace pwpt
