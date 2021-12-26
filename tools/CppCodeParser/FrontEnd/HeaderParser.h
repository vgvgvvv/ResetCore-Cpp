#pragma once


#include "BaseParser.h"


class CppCodeParser_API HeaderParser : public BaseParser
{
	DEFINE_DERIVED_CLASS(HeaderParser, BaseParser)
public:

	bool CompileDeclaration(SharedPtr<CppToken> Token);

};