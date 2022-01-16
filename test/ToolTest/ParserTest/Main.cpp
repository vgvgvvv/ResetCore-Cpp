
#include "CommonHeader.h"
#include "FrontEnd/BaseParser.h"
#include "SourceCode/CppSourceFile.h"
#include "TestFiles/TestClass.h"

int main()
{
	auto TestFileName = TestNamespace::TestClass::GetCurrentFileName();
	RE_LOG_INFO("Main", "Parse File : {}", TestFileName)
	CppSourceFile File(TestFileName);

	return 0;
}
