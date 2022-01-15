
#include "CommonHeader.h"
#include "FrontEnd/BaseParser.h"
#include "SourceCode/CppSourceFile.h"
#include "TestFiles/TestClass.h"

int main()
{
	CppSourceFile File(TestNamespace::TestClass::GetCurrentFileName());

	return 0;
}
