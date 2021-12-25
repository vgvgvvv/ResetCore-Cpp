#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"

class CppCodeParser_API CppSourceFile
{
public:
    CppSourceFile(const std::string& InFilePath)
        : FilePath(InFilePath)
    {
        Parse();
    }

private:

    void Parse()
    {
	    // TODO
    }

public:
	std::string FilePath;
};