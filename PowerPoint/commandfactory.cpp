
#include "cmd_add.h"
#include "cmd_help.h"
#include "cmd_print.h"
#include "cmd_redo.h"
#include "cmd_undo.h"
#include "commandfactory.h"

namespace pwpt
{

namespace Command
{

CFactory::CFactory()
{
	pwpt::ICommand_SPtr pAdd	= std::make_shared<CAddCmd>();
	pwpt::ICommand_SPtr pHelp	= std::make_shared<CHelpCmd>();
	pwpt::ICommand_SPtr pPrint	= std::make_shared<PrintCmd>();
	pwpt::ICommand_SPtr pRedo	= std::make_shared<CRedoCmd>();
	pwpt::ICommand_SPtr pUndo	= std::make_shared<CUndoCmd>();

	m_aCommands.emplace("add",		pAdd);
	m_aCommands.emplace("help",		pHelp);
	m_aCommands.emplace("print",	pPrint);
	m_aCommands.emplace("redo",		pRedo);
	m_aCommands.emplace("undo",		pUndo);
}

CFactory& CFactory::GetInstance()
{
	static CFactory oInstance{};

	return oInstance;
}

ICommand_SPtr CFactory::CreateCommand(std::string sCmd) const
{
	ICommand_SPtr pCommand = nullptr;

	if (m_aCommands.count(sCmd))
		pCommand = m_aCommands.at(sCmd)->Clone();

	return pCommand;
}

} // namespace Command

} // namespace pwpt
