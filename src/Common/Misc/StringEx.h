#pragma once
#include <string>
#include <vector>

#include "ResetCore_CommonLib_API.h"

namespace StringEx
{
	ResetCore_CommonLib_API void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
	ResetCore_CommonLib_API std::string WStringToString(const std::wstring& str);
	ResetCore_CommonLib_API std::wstring StringToWString(const std::string& str);
	ResetCore_CommonLib_API std::vector<std::string> Split(const std::string& str, const std::string& split);
}
