#pragma once

#include "BaseParser.h"

class CppSourceFile;

class CppCodeParser_API CppFileParser : public BaseParser
{
	DEFINE_DERIVED_CLASS(CppFileParser, BaseParser)

public:

	virtual bool CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	AString GetFileLocation(CppSourceFile& File) const;


private:

	bool CompileNamespaceDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileClassDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileClassMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileEnumDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileEnumMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileFunctionDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileFunctionMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileFieldDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);

	bool CompileFieldMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token);


};



