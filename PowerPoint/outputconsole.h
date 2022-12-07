
#ifndef _POWERPOINT_OUTPUTDEVICE_CONSOLE_HPP_
#define _POWERPOINT_OUTPUTDEVICE_CONSOLE_HPP_

#include <iostream>

#include "pwpt_ioutputdevice.h"

namespace pwpt
{

class COutputStream : public IOutputDevice
{
public:
	void Draw(IObject_SPtr) override;

private:
	std::ostream* m_pStream = &std::cout;
};
using OutputStream_SPtr = std::shared_ptr<COutputStream>;

} // namespace pwpt

#endif // _POWERPOINT_OUTPUTDEVICE_CONSOLE_HPP_
