
#include "actionfactory.h"
#include "toolbar_actions.h"

namespace pwpt
{

CActionFactory& CActionFactory::GetInstance()
{
	static CActionFactory oInstance{};

	return oInstance;
}

IAction_SPtr CActionFactory::CreateAction(ICommand_SPtr const& pCmd) const
{
	IAction_SPtr pAction = nullptr;
	
	if (pCmd == nullptr)
		return pAction;

	/*switch (pCmd->GetCommandType())
	{
	case EOperation::Set:
	{
		switch (pCmd->GetMainOption())
		{
		case EOption::Shape:
			pAction = std::make_shared<CShapeChanger>( );
		}
		break;
	}
		
	}*/
}

} // namespace pwpt
