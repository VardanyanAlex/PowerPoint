
#include <iostream>
#include <string>

#include "pwpt_appmanager.h"
#include "commandline.h"

namespace pwpt
{

void CCommandLine::Run()
{
	std::string sInput{};
	while (sInput != "exit")
	{
		std::ostream* pOutput = App::CAppManager::AppInstance().GetOutputStreamDevice();

		// prints symbol for differing commands from other context
		if (pOutput != nullptr)
			*pOutput << "==> ";

		std::getline(std::cin, sInput);
		if (!sInput.empty())
			emit InputDetected(sInput);


	}
}

} // namespace pwpt
