
#include "act_redo.h"
#include "cmd_redo.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 

CRedoCmd::CRedoCmd()
{}

void CRedoCmd::Execute()
{
	IAction_SPtr pAddSlide = std::make_shared<CRedo>();

	if (pAddSlide != nullptr)
		emit CreatedAction(pAddSlide);
}

ICommand_SPtr CRedoCmd::Clone() const
{
	return std::make_shared<CRedoCmd>(*this);
}

bool CRedoCmd::MainOptionRequired() const
{
	return false;
}

size_t CRedoCmd::RequiredMinOptionsCount() const
{
	return 0;
}

bool CRedoCmd::Acceptarg(std::string const& sOption, std::any oValue)
{
	return false;
}

bool CRedoCmd::Validate() const
{
	return true;
}

} // namespace Command

} // namespace pwpt
