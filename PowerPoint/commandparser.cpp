
#include <iostream>

#include "pwpt_icommand.h"
#include "commandfactory.h"
#include "commandparser.h"

namespace pwpt
{

namespace Command
{

pwpt::ICommand_SPtr CParser::Parse(std::istream& sInput)
{
	ICommand_SPtr pCommand = nullptr;
	
	SToken oToken = m_oTokenizer.NextToken(sInput);

	// Command name
	if (oToken.eType != ETokenType::Word)
		return pCommand;

	pCommand = CFactory::GetInstance().CreateCommand(oToken.sWord);

	if (!pCommand->MainOptionRequired() )
	{
		if (!sInput.eof())
			throw std::logic_error{ "invalid command!!!\n" };

		return pCommand;
	}

	// Main option (starts with --)
	oToken = m_oTokenizer.NextToken(sInput);
	if (oToken.eType != ETokenType::Word)
		throw std::logic_error{ "invalid command!!!\n" };

	bool bMainAccpeted = pCommand->AcceptMainOption(oToken.sWord);

	if (bMainAccpeted)
	{
		while (!sInput.eof())
		{
			oToken = m_oTokenizer.NextToken(sInput);
			if (oToken.eType != ETokenType::Word)
				throw std::logic_error{ "invalid command!!!\n" };

			SToken oSecondToken;
			if(!sInput.eof())
				oSecondToken = m_oTokenizer.NextToken(sInput);

			pCommand->Acceptarg(oToken.sWord, oSecondToken.GetValue());
		}
	}

	return pCommand;
}


} // namespace Command

} // namespace pwpt
