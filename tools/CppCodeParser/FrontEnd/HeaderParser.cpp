#include "HeaderParser.h"

DEFINE_DERIVED_CLASS_IMP(HeaderParser, BaseParser)

bool HeaderParser::CompileDeclaration(SharedPtr<CppToken> Token)
{
	return true;
}
