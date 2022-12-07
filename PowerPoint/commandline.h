
#ifndef _POWERPOINT_COMMANDLINE_HPP_
#define _POWERPOINT_COMMANDLINE_HPP_

#include "pwpt_icommandline.h"
#include "signal.h"

namespace pwpt
{

class CCommandLine : public ICommandLine
{
public:
	CCommandLine() =default;


	CCommandLine(CCommandLine const&) = delete;
	CCommandLine& operator=(CCommandLine const&) = delete;

	void Run() override;
	
};

} // namespace pwpt

#endif // _POWERPOINT_COMMANDLINE_HPP_
