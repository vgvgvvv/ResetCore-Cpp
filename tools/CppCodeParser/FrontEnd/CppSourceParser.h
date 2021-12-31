#pragma once

#include "CppFileParser.h"

class CppCodeParser_API CppSourceParser : public CppFileParser
{
	DEFINE_DERIVED_CLASS(CppSourceParser, CppFileParser)

public:
	bool CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token) override;
};

