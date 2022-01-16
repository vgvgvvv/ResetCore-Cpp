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

public:
	AString FilePath;
    AString Content;
    NestInfo NestInfo;

    SharedPtr<GlobalScope> FileScope;

public:
    DEFINE_GETTER_DECLTYPE(FileScope)

};

BEGIN_TO_JSON(CppSourceFile)
TO_JSON_ARG_WITH_GETTER(FileScope)
END_TO_JSON()

