#include "CppSourceFile.h"

#include "FrontEnd/CppSourceParser.h"
#include "FrontEnd/HeaderParser.h"
#include "Scopes/BaseScope.h"
#include "Scopes/ClassScope.h"
#include "Scopes/EnumScope.h"
#include "Scopes/FunctionScope.h"
#include "Scopes/GlobalScope.h"
#include "Scopes/NamespaceScope.h"

SharedPtr<BaseScope> NestInfo::GetCurrentScope()
{
	return ScopeInfo.top();
}

void NestInfo::PushScope(SharedPtr<BaseScope> NewScope)
{
	if(GlobalContext::Get().GetBoolValue("DebugCppFileParser"))
	{
		RE_LOG_INFO("NestInfo", "Push {0} : {1}",
			NewScope->GetClass()->Name(), NewScope->GetName())
	}
	ScopeInfo.push(NewScope);
}

SharedPtr<BaseScope> NestInfo::PopScope()
{
	SharedPtr<BaseScope> Scope = ScopeInfo.top();
	ScopeInfo.pop();
	if (GlobalContext::Get().GetBoolValue("DebugCppFileParser"))
	{
		RE_LOG_INFO("NestInfo", "Pop {0} : {1}",
			Scope->GetClass()->Name(), Scope->GetName())
	}
	return Scope;
}

SharedPtr<GlobalScope> CppSourceFile::Parse()
{
	if(!fs::exists(FilePath))
	{
		RE_LOG_ERROR("CppSourceFile::Parse", "Cannot Find Cpp Source Path {0}", FilePath.c_str())
		return nullptr;
	}
	Content = CommonLib::ReadFileIntoString(FilePath);

	SharedPtr<CppFileParser> Parser;

	fs::path FilePathInfo(FilePath);
	auto Extension = FilePathInfo.extension().string();
	if(Extension == ".h" || Extension == ".hpp")
	{
		Parser = std::make_shared<HeaderParser>();
	}
	else if(Extension == ".cpp" || Extension == "c")
	{
		Parser = std::make_shared<CppSourceParser>();
	}
	else
	{
		RE_LOG_WARN("CppSourceFile::Parse", "Invalid Cpp File Type %s", Extension.c_str())
		return nullptr;
	}

	Parser->InitParserSource(Content.c_str());

	NestInfo.PushScope(std::make_shared<GlobalScope>());

	while(true)
	{
		auto Token = Parser->GetToken();
		if(!Token)
		{
			break;
		}
		Parser->CompileDeclaration(*this, Token);
	}

	return std::static_pointer_cast<GlobalScope>(NestInfo.PopScope());
}
