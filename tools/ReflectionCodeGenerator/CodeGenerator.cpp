#include "CodeGenerator.h"

#include "CommonHeader.h"

class ICodeGenerator
{
public:
	void ExportFile(const AString& SourceFileName, const AString& GeneratedFileName);
};
