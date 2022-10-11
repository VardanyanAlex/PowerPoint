
#ifndef _POWERPOINT_CONSOLE_HPP_
#define _POWERPOINT_CONSOLE_HPP_

#include <iostream>

#include "parser.h"

class CConsole
{
public:
	CConsole();
	CCommand Run();
	//while(true)
	//GetInput()
	//Parse- provides material for CCommand
	//emit CCommand






private:
	std::istream* GetInput();

private:
	std::unique_ptr<CParser> pParser;
};

#endif // _POWERPOINT_CONSOLE_HPP_
