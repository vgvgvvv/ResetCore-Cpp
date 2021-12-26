
#include "CommonHeader.h"
#include "FrontEnd/BaseParser.h"
#include "FrontEnd/Token.h"

int main()
{
	BaseParser Parser;

	auto Content = CommonLib::ReadFileIntoString(
		"D:\\Documents\\MyProjects\\playground\\src\\resetcore-cpp\\tools\\CppCodeParser\\SourceCode\\Module.h");

	Parser.InitParserSource(Content.c_str());

	while(true)
	{
		auto Token = Parser.GetToken();
		if(!Token)
		{
			break;
		}
		RE_LOG_INFO("Token", "Current Token : {}", Token->GetTokenName().c_str());
	}

	return 0;
}
