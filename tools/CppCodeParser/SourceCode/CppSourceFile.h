#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"
#include "nlohmann/json.hpp"
#include "Json/JsonSerialization.h"
#include "Scopes/GlobalScope.h"


enum class ScopeType;
class BaseScope;
class GlobalScope;

class NestInfo
{
public:

    SharedPtr<BaseScope> GetCurrentScope();

    void PushScope(SharedPtr<BaseScope> NewScope);

    SharedPtr<BaseScope> PopScope();

    Stack<SharedPtr<BaseScope>> ScopeInfo;
};

class CppCodeParser_API CppSourceFile
{
public:
    CppSourceFile(const AString& InFilePath)
        : FilePath(InFilePath)
		, Content()
    {
        FileScope = Parse();
    }

    SharedPtr<GlobalScope> Parse();

    SharedPtr<GlobalScope> GetFileScope() const
    {
        return FileScope;
    }

public:
	AString FilePath;
    AString Content;
    NestInfo NestInfo;

    SharedPtr<GlobalScope> FileScope;
};


template<>
nlohmann::json ToJson<CppSourceFile>(const CppSourceFile& Obj)
{
    nlohmann::json Result;
    auto FileScope = Obj.GetFileScope();

	Result[std::string(GlobalScope::StaticClass()->Name())] = ToJson(*FileScope);

    return Result;
}