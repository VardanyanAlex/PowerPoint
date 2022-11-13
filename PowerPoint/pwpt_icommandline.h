
#ifndef _POWERPOINT_INTERFACE_ICOMMANDLINE_HPP_
#define _POWERPOINT_INTERFACE_ICOMMANDLINE_HPP_

#include <iostream>
#include <memory>

#include <QObject>

#include "pwpt_icommand.h"

namespace pwpt
{

using ICommandLine_Ptr = std::unique_ptr<class ICommandLine>;

class ICommandLine : public QObject
{
	Q_OBJECT

public:
	using DataStream_Ptr = std::unique_ptr<typename std::istream>;

	virtual void Run() = 0;
	virtual void ProcessInput(DataStream_Ptr) = 0;

signals:
	void commandConstructed(ICommand_Ptr);

}; // interface ICommandLine

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_ICOMMANDLINE_HPP_
