#include "BaseParser.h"

DEFINE_CLASS_IMP(BaseParser)

bool BaseParser::GetToken(Token& OutToken)
{
	return true;
}

bool BaseParser::CompileDeclaration(Token& Token)
{
	return true;
}
