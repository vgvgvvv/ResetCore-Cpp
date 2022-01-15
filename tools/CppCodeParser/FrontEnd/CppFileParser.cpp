#include "CppFileParser.h"

#include "Token.h"
#include "SourceCode/CppSourceFile.h"
#include "SourceCode/Scopes/BaseScope.h"
#include "SourceCode/Scopes/ClassScope.h"
#include "SourceCode/Scopes/EnumScope.h"
#include "SourceCode/Scopes/GlobalScope.h"
#include "SourceCode/Scopes/NamespaceScope.h"
#include "SourceCode/Scopes/GenerateInfos.h"

DEFINE_DERIVED_CLASS_IMP(CppFileParser, BaseParser)


bool CppFileParser::CompileDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{

	auto CurrentScope = File.NestInfo.GetCurrentScope();
	auto ScopeClass = CurrentScope->GetClass();
	if(Token->GetTokenName() == "namespace")
	{
		auto Succ = CompileNamespaceDeclaration(File, Token);
		if(Succ)
		{
			return true;
		}
	}

	if(Token->GetTokenName() == "RE_CLASS")
	{
		auto Succ = CompileClassDeclaration(File, Token);
		if (Succ)
		{
			return true;
		}
	}

	if (Token->GetTokenName() == "RE_ENUM")
	{
		auto Succ = CompileEnumDeclaration(File, Token);
		if (Succ)
		{
			return true;
		}
	}

	if(Token->GetTokenName() == "RE_FUNCTION")
	{
		auto Succ = CompileFunctionDeclaration(File, Token);
		if (Succ)
		{
			return true;
		}
	}

	if(Token->GetTokenName() == "RE_VAR")
	{
		auto Succ = CompileFieldDeclaration(File, Token);
		if (Succ)
		{
			return true;
		}
	}

	CurrentScope->CompileCurrentScope(*this, File, Token);

	if(Token->Matches('}'))
	{
		auto TopScopeClass = File.NestInfo.GetCurrentScope()->GetClass();
		if(TopScopeClass == NamespaceScope::StaticClass())
		{
			File.NestInfo.PopScope();
		}
		else if(TopScopeClass == ClassScope::StaticClass())
		{
			File.NestInfo.PopScope();
		}
	}

	return true;
}

bool CppFileParser::CompileNamespaceDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	auto NamespaceName = GetToken();
	RE_ASSERT_MSG(NamespaceName != nullptr, "Exit Early!");
	auto FrontBacket = GetToken();
	RE_ASSERT_MSG(FrontBacket != nullptr, "Exit Early!");
	if(!FrontBacket->Matches('{'))
	{
		return false;
	}

	auto NameSpaceScope = std::make_shared<NamespaceScope>(NamespaceName->GetTokenName());

	File.NestInfo.PushScope(NameSpaceScope);

	return true;
}

bool CppFileParser::CompileClassDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	CompileClassMarkDeclaration(File, Token);

	while(true)
	{
		auto Token = GetToken();
		RE_ASSERT_MSG(Token != nullptr, "Exit Early!");
		if(Token->Matches("class"))
		{
			break;
		}
	}

	auto ClassName = GetToken();
	RE_ASSERT_MSG(ClassName != nullptr, "Exit Early!");
	if(ClassName->GetTokenName().ends_with("_API"))
	{
		// 处理class XXX_API className的情况
		ClassName = GetToken();
		RE_ASSERT_MSG(ClassName != nullptr, "Exit Early!");
	}
	else
	{
		// 匹配class声明
		// class xxx;
		if(PeekSymbol(';'))
		{
			return false;
		}
	}

	RE_ASSERT_MSG(ClassName->GetTokenType() == CppTokenType::Identifier, "Exit Early!");

	auto CurrentClassScope = std::make_shared<ClassScope>(ClassName->GetTokenName());

	File.NestInfo.PushScope(CurrentClassScope);

	return true;
}

bool CppFileParser::CompileClassMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	RequireSymbol(')', GetFileLocation(File).c_str());
	return true;
}

bool CppFileParser::CompileEnumDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	CompileEnumMarkDeclaration(File, Token);

	RequireIdentifier("enum", GetFileLocation(File).c_str());

	// is enum class
	bool IsEnumClass = false;
	if(MatchIdentifier("class"))
	{
		IsEnumClass = true;
	}

	auto EnumNameToken = GetToken(true);

	RE_ASSERT_MSG(EnumNameToken->GetTokenType() != CppTokenType::Identifier
		, "Invalid Enum !! at {}", GetFileLocation(File).c_str());

	// enum name
	AString EnumName = EnumNameToken->GetTokenName();

	// 声明的情况
	if(MatchSymbol(';'))
	{
		return false;
	}

	// 处理 ": int8"
	if(MatchSymbol(':'))
	{
		auto EnumSizeType = GetToken();
		RE_ASSERT_MSG(EnumSizeType != nullptr && EnumSizeType->GetTokenType() == CppTokenType::Identifier
			, "Invalid Enum at {}", GetFileLocation(File).c_str())
	}

	// 进入
	RequireSymbol('{', GetFileLocation(File).c_str());

	auto CurrentEnumScope = std::make_shared<EnumScope>(EnumName);
	File.NestInfo.PushScope(CurrentEnumScope);

	auto EnumInfo = std::make_shared<EnumGenerateInfo>();
	EnumInfo->Name = EnumName;

	//TODO add enum info to scope
	File.NestInfo.GetCurrentScope()->AddEnum(EnumInfo);

	while(!MatchSymbol("}"))
	{
		// Handle Single line
		auto EnumValueNameToken = GetToken();
		RE_ASSERT_MSG(EnumValueNameToken && EnumValueNameToken->GetTokenType() == CppTokenType::Identifier
			, "Invalid EnumValue!! at {}", GetFileLocation(File).c_str());

		auto GenerateInfo = std::make_shared<EnumValueGenerateInfo>();
		GenerateInfo->Name = EnumValueNameToken->GetTokenName();
		CurrentEnumScope->GetFieldInfos().push_back(GenerateInfo);

		// next line
		while(!MatchSymbol(',')){}
	}

	File.NestInfo.PopScope();

	return true;
}

bool CppFileParser::CompileEnumMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	RequireSymbol(')', GetFileLocation(File).c_str());
	return true;
}

bool CppFileParser::CompileFunctionDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	// 分析RE_FUNCTION头
	CompileFunctionMarkDeclaration(File, Token);

	MemberFlag CurrentFlag = MemberFlag::None;

	while(true)
	{
		if(MatchToken([](auto& Token){ return Token.GetTokenName().ends_with("_API"); }))
		{
			continue;
		}
		if(MatchIdentifier("static"))
		{
			CurrentFlag |= MemberFlag::Static;
		}
		else if(MatchIdentifier("virtual"))
		{
			CurrentFlag |= MemberFlag::Virtual;
		}
		//TODO
	}

	auto CurrentScope = File.NestInfo.GetCurrentScope();
	if(CurrentScope->GetClass() == ClassScope::StaticClass())
	{
		
	}
	else if(CurrentScope->GetClass() == GlobalScope::StaticClass() || CurrentScope->GetClass() == NamespaceScope::StaticClass())
	{
		
	}
	return true;
}

bool CppFileParser::CompileFunctionMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	RequireSymbol(')', GetFileLocation(File).c_str());
}

bool CppFileParser::CompileFieldDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	CompileFieldMarkDeclaration(File, Token);

	// access type
	MemberAccessType AccessType = MemberAccessType::None;
	auto CurrentScope = File.NestInfo.GetCurrentScope();
	if(CurrentScope->GetClass() == ClassScope::StaticClass())
	{
		auto CurrentClassScope = std::static_pointer_cast<ClassScope>(CurrentScope);
		AccessType = CurrentClassScope->GetCurrentAccessType();
	}

	// member flag
	MemberFlag CurrentFlag = MemberFlag::None;
	// function decorator
	while (true)
	{
		if (MatchToken([](auto& Token) { return Token.GetTokenName().ends_with("_API"); }))
		{
			continue;
		}
		if (MatchIdentifier("static"))
		{
			CurrentFlag |= MemberFlag::Static;
			continue;
		}
		else if (MatchIdentifier("virtual"))
		{
			CurrentFlag |= MemberFlag::Virtual;
			continue;
		}
		else if(MatchIdentifier("const"))
		{
			CurrentFlag |= MemberFlag::Const;
			continue;
		}
		break;
	}

	// member owner type
	MemberOwnerType OwnerType = MemberOwnerType::None;
	if (CurrentScope->GetClass() == ClassScope::StaticClass())
	{
		OwnerType = MemberOwnerType::ClassMember;
	}
	else
	{
		OwnerType = MemberOwnerType::Global;
	}

	// field name
	AString FieldName = "";

	// field type 
	Type FieldType;

	FieldInfo Field(FieldName, AccessType, CurrentFlag, OwnerType, &FieldType);
	

	return true;
}

bool CppFileParser::CompileFieldMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	RequireSymbol(')', GetFileLocation(File).c_str());
}

AString CppFileParser::GetFileLocation(CppSourceFile& File) const
{
	return fmt::format("file : {0}  position : {1}", File.FilePath.c_str(), GetLocation().c_str());
}

