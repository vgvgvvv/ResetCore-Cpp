#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"

class CppCodeParser_API CppSourceFile
{
public:
    CppSourceFile(const String& InFilePath)
        : FilePath(InFilePath)
		, Content()
    {
        Parse();
    }

private:

    void Parse();

public:
	String FilePath;
    WString Content;
};