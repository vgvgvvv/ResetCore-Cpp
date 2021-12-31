#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"


enum class ScopeType;
class BaseScope;

class NestInfo
{
public:

    SharedPtr<BaseScope> GetCurrentScope();

    void PushScope(SharedPtr<BaseScope> Scope);

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
        Parse();
    }

private:

    void Parse();

public:
	AString FilePath;
    AString Content;
    NestInfo NestInfo;
};