
#ifndef _POWERPOINT_INTERFACE_IOUTPUTDEVICE_HPP_
#define _POWERPOINT_INTERFACE_IOUTPUTDEVICE_HPP_

#include <memory>

#include "pwpt_iobject.h"

namespace pwpt
{
	
class IOutputDevice
{
public:
	//virtual void Draw(IObject_SPtr) = 0;
};
using OutputDevice_SPtr = std::shared_ptr<class IOutputDevice>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_IOUTPUTDEVICE_HPP_
