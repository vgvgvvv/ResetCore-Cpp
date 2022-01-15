#include "CppSourceParser.h"


DEFINE_DERIVED_CLASS_IMP(CppSourceParser, CppFileParser)

bool CppSourceParser::CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return Super::CompileDeclaration(File, Token);
}
