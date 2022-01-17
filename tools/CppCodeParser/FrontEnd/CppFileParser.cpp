#include "CppFileParser.h"

#include "Token.h"
#include "SourceCode/CppSourceFile.h"
#include "SourceCode/Scopes/BaseScope.h"
#include "SourceCode/Scopes/ClassScope.h"
#include "SourceCode/Scopes/EnumScope.h"
#include "SourceCode/Scopes/FunctionScope.h"
#include "SourceCode/Scopes/GlobalScope.h"
#include "SourceCode/Scopes/NamespaceScope.h"
#include "SourceCode/Scopes/GenerateInfos.h"

DEFINE_DERIVED_CLASS_IMP(CppFileParser, BaseParser)

StaticGlobalContextValue GVarDebugCppFileParser("DebugCppFileParser", true);

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

	if(Token->GetTokenName() == "RE_FIELD")
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
	auto NamespaceNameToken = GetToken();
	RE_ASSERT_MSG(NamespaceNameToken != nullptr, "Exit Early!");
	auto FrontBacket = GetToken();
	RE_ASSERT_MSG(FrontBacket != nullptr, "Exit Early!");
	if(!FrontBacket->Matches('{'))
	{
		return false;
	}

	auto NamespaceName = NamespaceNameToken->GetTokenName();

	auto CurrentScope = File.NestInfo.GetCurrentScope();

	SharedPtr<NamespaceScope> CurrentNamespaceScope = 
		std::make_shared<NamespaceScope>(NamespaceName);

	SharedPtr<NamespaceGenerateInfo> NamespaceInfo = std::make_shared<NamespaceGenerateInfo>();
	NamespaceInfo->NamespaceName = NamespaceName;
	NamespaceInfo->Scope = CurrentNamespaceScope;

	CurrentScope->AddNamespace(NamespaceInfo);

	File.NestInfo.PushScope(CurrentNamespaceScope);

	return true;
}

bool CppFileParser::CompileClassDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	CompileClassMarkDeclaration(File, Token);

	while(true)
	{
		auto Token = GetToken();
		RE_ASSERT_MSG(Token != nullptr, "Exit Early!");
		if(Token->Matches("class") || Token->Matches("struct"))
		{
			break;
		}
	}

	auto ClassNameToken = GetToken();
	RE_ASSERT_MSG(ClassNameToken != nullptr, "Exit Early!");
	if(ClassNameToken->GetTokenName().ends_with("_API"))
	{
		// 处理class XXX_API className的情况
		ClassNameToken = GetToken();
		RE_ASSERT_MSG(ClassNameToken != nullptr, "Exit Early!");
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

	RE_ASSERT_MSG(ClassNameToken->GetTokenType() == CppTokenType::Identifier, "Exit Early!");


	auto ClassName = ClassNameToken->GetTokenName();
	auto CurrentClassScope = std::make_shared<ClassScope>(ClassName);

	auto ClassInfo = std::make_shared<ClassGenerateInfo>();
	ClassInfo->GenerateClassName = ClassName;
	ClassInfo->Scope = CurrentClassScope;

	File.NestInfo.GetCurrentScope()->AddClass(ClassInfo);

	File.NestInfo.PushScope(CurrentClassScope);

	return true;
}

bool CppFileParser::CompileClassMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	auto Tokens = GetTokensUntilPairMatch('(', ')');
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

	RE_ASSERT_MSG(EnumNameToken->GetTokenType() == CppTokenType::Identifier
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

	auto EnumInfo = std::make_shared<EnumGenerateInfo>();
	EnumInfo->Name = EnumName;
	EnumInfo->IsClassEnum = IsEnumClass;
	EnumInfo->Scope = CurrentEnumScope;

	//TODO add enum info to scope
	File.NestInfo.GetCurrentScope()->AddEnum(EnumInfo);

	File.NestInfo.PushScope(CurrentEnumScope);

	PrintDebugInfo("Enter " + CurrentEnumScope->GetName());


	while(true)
	{
		// Handle Single line
		auto EnumValueNameToken = GetToken();
		RE_ASSERT_MSG(EnumValueNameToken && EnumValueNameToken->GetTokenType() == CppTokenType::Identifier
			, "Invalid EnumValue!! at {}", GetFileLocation(File).c_str());

		auto GenerateInfo = std::make_shared<EnumValueGenerateInfo>();
		GenerateInfo->Name = EnumValueNameToken->GetTokenName();
		CurrentEnumScope->GetFieldInfos().push_back(GenerateInfo);

		PrintDebugInfo("Enum Value : " + GenerateInfo->Name);

		bool ExitEnumBody = false;
		// next line
		while(!MatchSymbol(','))
		{
			if(MatchSymbol('}'))
			{
				ExitEnumBody = true;
				break;
			}
			GetToken();
		}

		if(ExitEnumBody)
		{
			break;
		}
	}

	PrintDebugInfo("Exit " + CurrentEnumScope->GetName());

	// 退出
	File.NestInfo.PopScope();

	return true;
}

bool CppFileParser::CompileEnumMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	auto Tokens = GetTokensUntilPairMatch('(', ')');
	return true;
}

bool CppFileParser::CompileFunctionDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	// 分析RE_FUNCTION头
	CompileFunctionMarkDeclaration(File, Token);

	auto FunctionInfo = std::make_shared<FunctionGenerateInfo>();
	auto CurrentScope = File.NestInfo.GetCurrentScope();
	CurrentScope->AddMethod(FunctionInfo);


	// access type and owner type
	{
		if (CurrentScope->GetClass() == ClassScope::StaticClass())
		{
			auto CurrentClassScope = std::static_pointer_cast<ClassScope>(CurrentScope);
			FunctionInfo->AccessType = CurrentClassScope->GetCurrentAccessType();
			FunctionInfo->OwnerType = MemberOwnerType::ClassMember;
		}
		else
		{
			FunctionInfo->AccessType = MemberAccessType::None;
			FunctionInfo->OwnerType = MemberOwnerType::Global;
		}
	}


	// flag
	{
		MemberFlag CurrentFlag = MemberFlag::None;
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
				FunctionInfo->ReturnTypeName.IsConst = true;
			}
			else if(MatchIdentifier("class"))
			{
				continue;
			}
			else if(MatchIdentifier("inline"))
			{
				continue;
			}
			//TODO some other identify
			break;
		}

		FunctionInfo->Flag = CurrentFlag;
	}

	// get token until '('
	auto TokensBeforeParams = 
		GetTokensUntil([](CppToken& Token) {return Token.Matches('('); });

	// last is '(' second last is function name
	auto FunctionNameToken = TokensBeforeParams[TokensBeforeParams.size() - 2];
	auto FunctionName = FunctionNameToken->GetTokenName();
	FunctionInfo->FunctionName = FunctionName;

	// TODO return param
	// only support single identifier typename, dont use like "unsigned int"
	//auto ReturnParamToken = GetToken(true);

	auto TokenBeforeParamsEnd = GetTokensUntilPairMatch('(', ')');

	// TODO arg params
	// RE_ASSERT_MSG(ReturnParamToken != nullptr && ReturnParamToken->GetTokenType() == CppTokenType::Identifier, 
	// 	"Invalid Function Return Type Name !! at {}", GetFileLocation(File).c_str())

	// function end with const
	if(MatchIdentifier("const"))
	{
		FunctionInfo->Flag |= MemberFlag::Const;
	}

	if(MatchSymbol('=') && MatchSymbol('0'))
	{
		FunctionInfo->Flag |= MemberFlag::Abstruct;
	}

	if(MatchSemi())
	{
		return true;
	}

	RequireSymbol('{', GetFileLocation(File).c_str());

	PrintDebugInfo("Add Function " + FunctionName);

	auto Scope = std::make_shared<FunctionScope>(FunctionName);
	FunctionInfo->Scope = Scope;

	File.NestInfo.PushScope(Scope);

	GetTokensUntilPairMatch('{', '}');

	File.NestInfo.PopScope();
	
	return true;
}

bool CppFileParser::CompileFunctionMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	auto Tokens = GetTokensUntilPairMatch('(', ')');
	return true;
}

bool CppFileParser::CompileFieldDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	CompileFieldMarkDeclaration(File, Token);

	auto CurrentScope = File.NestInfo.GetCurrentScope();
	auto FieldInfo = std::make_shared<FieldGenerateInfo>();

	CurrentScope->AddField(FieldInfo);

	// access type and owner type
	{
		MemberAccessType AccessType = MemberAccessType::None;
		if (CurrentScope->GetClass() == ClassScope::StaticClass())
		{
			auto CurrentClassScope = std::static_pointer_cast<ClassScope>(CurrentScope);
			FieldInfo->AccessType = CurrentClassScope->GetCurrentAccessType();
			FieldInfo->OwnerType = MemberOwnerType::ClassMember;
		}
		else
		{
			FieldInfo->AccessType = MemberAccessType::None;
			FieldInfo->OwnerType = MemberOwnerType::Global;
			
		}
	}
	
	// member flag
	{
		MemberFlag CurrentFlag = MemberFlag::None;
		// field decorator
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
			else if (MatchIdentifier("const"))
			{
				CurrentFlag |= MemberFlag::Const;
				continue;
			}
			else if (MatchIdentifier("class"))
			{
				continue;
			}
			break;
		}
		FieldInfo->Flag = CurrentFlag;
	}
	
	auto TokensBeforeDefine = GetTokensUntil(
		[](CppToken& Token) {return Token.Matches('=') || Token.Matches(';'); });

	RE_ASSERT_MSG(TokensBeforeDefine.size() > 2, "Invalid Field Definition !! at {}", GetFileLocation(File));

	// field name
	auto FieldNameToken = TokensBeforeDefine[TokensBeforeDefine.size() - 2];
	auto FieldName = FieldNameToken->GetTokenName();

	FieldInfo->FieldName = FieldName;

	PrintDebugInfo("Add Field " + FieldName);

	// field type
	// TODO

	if(TokensBeforeDefine[TokensBeforeDefine.size()-1]->Matches('='))
	{
		GetTokenUntilMatch(';');
	}
	

	return true;
}

bool CppFileParser::CompileFieldMarkDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	RequireSymbol('(', GetFileLocation(File).c_str());
	auto Tokens = GetTokensUntilPairMatch('(', ')');
	return true;
}

bool CppFileParser::CompileAttributeDeclaration(CppSourceFile& File, SharedPtr<CppToken> Token)
{
	// TODO
	return true;
}

void CppFileParser::PrintDebugInfo(const AString& Info)
{
	if(GlobalContext::Get().GetBoolValue("DebugCppFileParser"))
	{
		RE_LOG_INFO("PrintDebugInfo", "{}", Info.c_str());
	}
}

AString CppFileParser::GetFileLocation(CppSourceFile& File) const
{
	return fmt::format("file : {0}  position : {1}", File.FilePath.c_str(), GetLocation().c_str());
}

