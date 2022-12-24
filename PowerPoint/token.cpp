
#include "token.h"

namespace pwpt
{
//////////////////////////////////////////////////////////////
namespace Command
{

std::any SToken::GetValue() const
{
	switch (eType)
	{
	case ETokenType::Number:
		return iNumber;
		break;
	case ETokenType::Punct:
		return cPunct;
		break;
	case ETokenType::Word:
		return sWord;
		break;
	default:
		return std::string{};
		break;
	}
}

} // namespace Command

} // namespace pwpt
