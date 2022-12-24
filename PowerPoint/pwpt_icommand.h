
#ifndef _POWERPOINT_INTERFACE_ICOMMAND_HPP_
#define _POWERPOINT_INTERFACE_ICOMMAND_HPP_

#include <any>
#include <exception>
#include <memory>
#include <queue>

#include <QObject>

#include "pwpt_iaction.h"

namespace pwpt
{

namespace Command
{ 
//////////////////////////////////////////////////////////////
/// Interface ICommand
//////////////////////////////////////////////////////////////
class ICommand : public QObject
{
	Q_OBJECT

public:
	virtual void Execute() = 0;
	virtual std::shared_ptr<ICommand> Clone() const = 0;
	
	virtual bool MainOptionRequired() const = 0;
	virtual size_t RequiredMinOptionsCount() const = 0;

	virtual bool Acceptarg(std::string const&, std::any oValue) = 0;
	virtual bool Validate() const = 0;

	virtual bool AcceptMainOption(std::string const&);

signals:
	void CreatedAction(IAction_SPtr&);

protected:
	ICommand() = default;
	ICommand(ICommand const&);

protected:
	std::vector<std::string> m_aAcceptedOptions;

	std::string m_sMainOption{};
	std::map<std::string, std::any> m_aOptValues;
};
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
class CCmdExecException : public std::exception
{
public:
	CCmdExecException(std::string const& sErrorMessage);

	const char* what() const noexcept override;

private:
	std::string m_sErrorMessage;
};
//////////////////////////////////////////////////////////////
} // namespace Command
using ICommand_SPtr = std::shared_ptr<class Command::ICommand>;
using ICommandsList = std::queue<ICommand_SPtr>;
} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMAND_HPP_
