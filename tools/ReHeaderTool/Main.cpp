
#include "CommonHeader.h"
#include "ReHeaderTool.h"
#include "SourceCode/Project.h"

int main()
{
	RE_LOG_INFO(LogReHeaderTool, "Hello World")

	CppProject Project;
	Project.Load(Path::GetSourcePath());


	return 0;
}
