#include "CppSourceFile.h"

#include "FrontEnd/CppSourceParser.h"
#include "FrontEnd/HeaderParser.h"

void CppSourceFile::Parse()
{
	if(!fs::exists(FilePath))
	{
		RE_LOG_ERROR("CppSourceFile::Parse", "Cannot Find Cpp Source Path {0}", FilePath.c_str())
		return;
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
		return;
	}

	Parser->InitParserSource(Content.c_str());

	while(true)
	{
		auto Token = Parser->GetToken();
		if(!Token)
		{
			break;
		}
		Parser->CompileDeclaration(*this, Token);
	}
}
