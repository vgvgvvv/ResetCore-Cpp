#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"

class Token;

class CppCodeParser_API BaseParser
{
	DEFINE_CLASS(BaseParser)
public:

	const TCHAR* Input;

	bool GetToken(Token& OutToken);

	bool CompileDeclaration(Token& Token);

};
