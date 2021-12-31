#include "CppFileParser.h"

#include "Token.h"
#include "SourceCode/CppSourceFile.h"
#include "SourceCode/Scopes/BaseScope.h"
#include "SourceCode/Scopes/ClassScope.h"
#include "SourceCode/Scopes/GlobalScope.h"
#include "SourceCode/Scopes/NamespaceScope.h"

DEFINE_DERIVED_CLASS_IMP(CppFileParser, BaseParser)


bool CppFileParser::CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{

	auto CurrentScope = File.NestInfo.GetCurrentScope();
	auto ScopeClass = CurrentScope->GetClass();
	if(Token->GetTokenName() == "namespace")
	{
		auto Succ = CompileNamespaceDeclaration(File, Token);
	}

	if(Token->GetTokenName() == "RE_CLASS")
	{
		auto Succ = CompileClassDeclaration(File, Token);
	}

	if (Token->GetTokenName() == "RE_ENUM")
	{
		
	}

	if(Token->GetTokenName() == "RE_FUNCTION")
	{
		if(ScopeClass->IsA(ClassScope::StaticClass()))
		{
			auto Succ = CompileClassFunctionDeclaration(File, Token);
		}
		else if(ScopeClass->IsA(GlobalScope::StaticClass()) || ScopeClass->IsA(NamespaceScope::StaticClass()))
		{
			auto Succ = CompileGlobalFunctionDeclaration(File, Token);
		}
	}

	if(Token->GetTokenName() == "RE_VAR")
	{
		if (ScopeClass->IsA(ClassScope::StaticClass()))
		{
			auto Succ = CompileClassMemberDeclaration(File, Token);
		}
		else if (ScopeClass->IsA(GlobalScope::StaticClass()) || ScopeClass->IsA(NamespaceScope::StaticClass()))
		{
			auto Succ = CompileGlobalMemberDeclaration(File, Token);
		}
	}


	return true;
}

bool CppFileParser::CompileNamespaceDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
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
