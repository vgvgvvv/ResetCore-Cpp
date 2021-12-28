#pragma once

#include "BaseParser.h"

class CppSourceFile;

class CppCodeParser_API CppFileParser : public BaseParser
{
	DEFINE_DERIVED_CLASS(CppFileParser, BaseParser)

public:

	virtual bool CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

};