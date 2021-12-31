#pragma once

#include "CppFileParser.h"


class CppCodeParser_API HeaderParser : public CppFileParser
{
	DEFINE_DERIVED_CLASS(HeaderParser, CppFileParser)

public:
	bool CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token) override;
};
