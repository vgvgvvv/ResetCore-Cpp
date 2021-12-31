#include "CppFileParser.h"

#include "Token.h"

DEFINE_DERIVED_CLASS_IMP(CppFileParser, BaseParser)


bool CppFileParser::CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{

	if(Token->GetTokenName() == "RE_CLASS")
	{
		
	}

	return true;
}

bool CppFileParser::CompileClassDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return true;
}

bool CppFileParser::CompileClassFunctionDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return true;
}

bool CppFileParser::CompileClassMemberDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return true;
}

bool CppFileParser::CompileGlobalFunctionDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return true;
}

bool CppFileParser::CompileGlobalMemberDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	return true;
}
