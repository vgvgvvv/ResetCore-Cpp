
#include "CommonHeader.h"
#include "FrontEnd/BaseParser.h"
#include "SourceCode/CppSourceFile.h"
#include "TestFiles/TestClass.h"

int main()
{
	auto TestFileName = TestNamespace::TestClass::GetCurrentFileName();
	RE_LOG_INFO("Main", "Parse File : {}", TestFileName)
	CppSourceFile File(TestFileName);

	auto Json = File.ToJson();

	RE_LOG_INFO("Main", "{}", Json.dump(4).c_str())

	return 0;
}
