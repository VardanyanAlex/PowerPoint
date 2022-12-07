
#include "command.h"
#include "commandfactory.h"

namespace pwpt
{

namespace Command
{

CFactory::CFactory()
{
	pwpt::ICommand_SPtr pPrint = std::make_shared<PrintCmd>();

	m_aCommands.emplace("print", pPrint);
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
