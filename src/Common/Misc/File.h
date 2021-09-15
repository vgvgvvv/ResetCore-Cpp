#pragma once
#include <string>
#include "ResetCore_CommonLib_API.h"

namespace CommonLib
{
	ResetCore_CommonLib_API std::string ReadFileIntoString(const std::string& path);
	ResetCore_CommonLib_API void SaveStringIntoFile(const std::string& content, const std::string& path);
}
