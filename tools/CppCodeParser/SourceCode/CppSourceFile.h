#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"
#include "nlohmann/json.hpp"
#include "Json/ToJsonDefine.h"
#include "Scopes/GlobalScope.h"


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
    DEFINE_CLASS(CppSourceFile)
    DEFINE_TO_JSON_MEMBER()
public:
    CppSourceFile(const AString& InFilePath)
        : FilePath(InFilePath)
		, Content()
    {
        FileScope = Parse();
    }

    SharedPtr<GlobalScope> Parse();

public:
	AString FilePath;
    AString Content;
    NestInfo NestInfo;

    SharedPtr<GlobalScope> FileScope;

public:
    DEFINE_GETTER_DECLTYPE(FileScope)

};



