#include "CppSourceFile.h"

void CppSourceFile::Parse()
{
	if(!fs::exists(FilePath))
	{
		RE_LOG_ERROR("CppSourceFile::Parse", "Cannot Find Cpp Source Path {0}", FilePath.c_str())
		return;
	}
	Content = CommonLib::ReadFileIntoWString(FilePath);
}
