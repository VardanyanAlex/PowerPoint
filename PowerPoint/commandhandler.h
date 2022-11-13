
#ifndef _POWERPOINT_COMMAND_HANDLER_HPP_
#define _POWERPOINT_COMMAND_HANDLER_HPP_

#include "pwpt_icommandhandler.h"
#include "pwpt_idoceditor.h"

namespace pwpt
{

class CCommandHandler : public IHandler
{
public:
	CCommandHandler();

	CCommandHandler(CCommandHandler const&) = delete;
	CCommandHandler& operator=(CCommandHandler const&) = delete;


	//void SetEditor(CEditor&) override;

	EState Handle(ICommand_Ptr&) override;

public slots:
	void OnCommandConstructed(ICommand_Ptr) override;

private:
	IDocEditor_Ptr m_pEditor;

};

} // namespace pwpt

#endif // _POWERPOINT_COMMAND_HANDLER_HPP_
