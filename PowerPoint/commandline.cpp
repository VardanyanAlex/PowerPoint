
#include <iostream>
#include <string>

#include "commandline.h"

namespace pwpt
{

void CCommandLine::Run()
{
	std::string sInput{};
	while (sInput != "exit")
	{
		std::getline(std::cin, sInput);
		if (!sInput.empty())
			emit InputDetected(sInput);
	}
}

} // namespace pwpt
