#pragma once
#include "CommonHeader.h"
#include "Class/Class.h"
#include "CppCodeParser_API.h"




class CppCodeParser_API BaseToken
{
	DEFINE_CLASS(BaseToken)
public:
	enum { NAME_SIZE = 1024 };
};

class CppCodeParser_API IdentifierToken : public BaseToken
{
	DEFINE_DERIVED_CLASS(IdentifierToken, BaseToken)
};

class CppCodeParser_API SymbolToken : public BaseToken
{
	DEFINE_DERIVED_CLASS(SymbolToken, BaseToken)
};

