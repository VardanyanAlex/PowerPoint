
#ifndef _POWERPOINT_APP_MANAGER_HPP_
#define _POWERPOINT_APP_MANAGER_HPP_

#include "pwpt_app.h"

namespace pwpt
{

namespace App
{

class CAppManager
{
public:
	CAppManager(CAppManager const&) = delete;
	CAppManager& operator=(CAppManager const&) = delete;

	static CApp& AppInstance();

private:
	CAppManager();
};

} // namespace App

} // namespace pwpt

#endif // _POWERPOINT_APP_MANAGER_HPP_