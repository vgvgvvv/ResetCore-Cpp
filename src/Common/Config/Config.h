#pragma once
#include <string>

#include "inifile.h"
#include "ResetCore_CommonLib_API.h"

class ResetCore_CommonLib_API Config
{
public:
	static bool LoadConfig(const std::string& config, inifile::IniFile* iniFile);
	static bool LoadConfigByName(const std::string& name, inifile::IniFile* iniFile);
};
