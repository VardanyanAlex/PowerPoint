
#ifndef _POWERPOINT_INTERFACE_IMACHINE_HPP_
#define _POWERPOINT_INTERFACE_IMACHINE_HPP_

#include <iostream>
#include <memory>

#include <QObject>

#include "pwpt_iaction.h"

namespace pwpt
{

class IMachine : public QObject
{
	Q_OBJECT

public:
	virtual void Do(IAction_SPtr&) = 0;

public slots:
	virtual void onActionCreated(IAction_SPtr&) = 0;

};
using IMachine_SPtr = std::shared_ptr<class IMachine>;
using IMachine_UPtr = std::unique_ptr<class IMachine>;

} // namespace pwpt

#endif // _POWERPOINT_INTERFACE_IDOCUMENT_EDITOR_HPP_
