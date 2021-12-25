#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <functional>

#include "ResetCore_CommonLib_API.h"

namespace fs = std::filesystem;

namespace CommonLib
{
	ResetCore_CommonLib_API void GetFiles(const std::string& Path, std::vector<fs::directory_entry>& OutFiles, bool OnlyTop = true);
	ResetCore_CommonLib_API void GetFilesWithCondition(const std::string& Path, std::vector<fs::directory_entry>& OutFiles, std::function<bool(const fs::directory_entry&)> Condition, bool OnlyTop = true);
	ResetCore_CommonLib_API void GetDirectories(const std::string& Path, std::vector<fs::directory_entry>& OutDirectories);

}