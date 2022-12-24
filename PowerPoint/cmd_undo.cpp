
#include "act_undo.h"
#include "cmd_undo.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////////////
namespace Command
{ 

CUndoCmd::CUndoCmd()
{}

void CUndoCmd::Execute()
{
	IAction_SPtr pAddSlide = std::make_shared<CUndo>();

	if (pAddSlide != nullptr)
		emit CreatedAction(pAddSlide);
}

ICommand_SPtr CUndoCmd::Clone() const
{
	return std::make_shared<CUndoCmd>(*this);
}

bool CUndoCmd::MainOptionRequired() const
{
	return false;
}

size_t CUndoCmd::RequiredMinOptionsCount() const
{
	return 0;
}

bool CUndoCmd::Acceptarg(std::string const& sOption, std::any oValue)
{
	return false;
}

bool CUndoCmd::Validate() const
{
	return true;
}

} // namespace Command

} // namespace pwpt
