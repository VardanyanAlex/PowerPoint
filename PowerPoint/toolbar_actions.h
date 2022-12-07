
#ifndef _POWERPOINT_TOOLBAR_ACTIONS_HPP_
#define _POWERPOINT_TOOLBAR_ACTIONS_HPP_

#include <memory>

#include <QColor>

#include "pwpt_iaction.h"
#include "tools.h"

namespace pwpt
{

class CShapeChanger : public IAction
{
public:
	CShapeChanger(EShape const = EShape::None);

	void Run() override;

private:
	EShape m_eShape = EShape::None;
	
};

class CThicknessChanger : public IAction
{
public:
	CThicknessChanger(ELineThickness const = ELineThickness::Medium);

	void Run() override;

private:
	ELineThickness m_eThickness = ELineThickness::Medium;

};

class CColorChanger : public IAction
{
public:
	CColorChanger(QColor const = Qt::black);

	void Run() override;

private:
	QColor m_oColor = Qt::black;

};

} // namespace pwpt

#endif // _POWERPOINT_TOOLBAR_ACTIONS_HPP_
