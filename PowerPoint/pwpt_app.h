
#ifndef _POWERPOINT_ABSTRACT_APP_HPP_
#define _POWERPOINT_ABSTRACT_APP_HPP_

#include <iostream>
#include <memory>

#include "pwpt_idocument.h"
#include "pwpt_ioutputdevice.h"

namespace pwpt
{

namespace App
{

class CApp
{
public:
	CApp(CApp const&) = delete;
	CApp& operator=(CApp const&) = delete;

	virtual void Run() = 0;
	
	PwPtDoc_SPtr GetDocument() const;
	std::ostream* GetOutputStreamDevice() const;

protected:
	CApp() =default;

protected:
	PwPtDoc_SPtr			m_pDocument		= nullptr;
	std::ostream*			m_pOutputStream = &std::cout;
};

} // namespace App

} // namespace pwpt

#endif // _POWERPOINT_ABSTRACT_APP_HPP_
