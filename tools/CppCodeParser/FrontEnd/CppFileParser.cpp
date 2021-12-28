#include "CppFileParser.h"

DEFINE_DERIVED_CLASS_IMP(CppFileParser, BaseParser)


bool CppFileParser::CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return true;
}
