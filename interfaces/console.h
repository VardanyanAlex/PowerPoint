
#ifndef _POWERPOINT_CONSOLE_HPP_
#define _POWERPOINT_CONSOLE_HPP_

#include <iostream>

#include "parser.h"
#include "pwpt_icommandline.h"

class CConsole : public pwpt::Command::ICommandLine
{
public:
	CConsole();
	void Run() override;
	//while(true)
	//GetInput()
	//Parse- returns CCommand
	//emit CCommand

// signals:
	void commandConstructed(pwpt::ICommand_Ptr) override;

private:
	std::istream* GetInput();

private:
	std::unique_ptr<CParser> pParser;
};

#endif // _POWERPOINT_CONSOLE_HPP_
