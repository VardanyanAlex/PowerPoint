
#include "application.h"
#include "pwpt_appmanager.h"

namespace pwpt
{

namespace App
{

CApp& CAppManager::AppInstance()
{
	// Meyers' singleton
	static CPowerpointApp oApp;

	return oApp;
}

CAppManager::CAppManager()
{}

} // namespace App

} // namespace pwpt
