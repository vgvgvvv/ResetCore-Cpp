#include "HeaderParser.h"

DEFINE_DERIVED_CLASS_IMP(HeaderParser, CppFileParser)

bool HeaderParser::CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return Super::CompileDeclaration(File, Token);
}
