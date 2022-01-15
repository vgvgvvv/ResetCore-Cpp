#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"


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
        Parse();
    }

    SharedPtr<GlobalScope> Parse();

public:
	AString FilePath;
    AString Content;
    NestInfo NestInfo;
};