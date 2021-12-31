#pragma once

#include "BaseParser.h"

class CppSourceFile;

class CppCodeParser_API CppFileParser : public BaseParser
{
	DEFINE_DERIVED_CLASS(CppFileParser, BaseParser)

public:

	virtual bool CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

private:

	bool CompileNamespaceDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileClassDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileClassFunctionDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileClassMemberDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileGlobalFunctionDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileGlobalMemberDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

};