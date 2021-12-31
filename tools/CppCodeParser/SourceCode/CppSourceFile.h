#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"


class BaseScope;

class NestInfo
{
public:

    Queue<SharedPtr<BaseScope>> ScopeInfo;
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