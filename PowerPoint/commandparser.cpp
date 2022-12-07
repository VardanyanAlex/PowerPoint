
#include <iostream>

#include "command.h"
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

	if (oToken.eType != ETokenType::Word)
		return pCommand;

	pCommand = CFactory::GetInstance().CreateCommand(oToken.sWord);

	while (!sInput.eof())
	{
		EOption eOption{};
		SOptionValue oValue{};
		
		oToken = m_oTokenizer.NextToken(sInput);
		//if (oToken.eType == ETokenType::Option)
		//	eOption = oToken.eOption;

		//oToken = m_oTokenizer.NextToken(sInput);
		//if (oToken.eType == ETokenType::OptionValue)
		//	oValue = oToken.oValue;

		//pCommand->AddOptionAndValue(eOption, oValue);
	}
	

	return pCommand;
}


} // namespace Command

} // namespace pwpt
