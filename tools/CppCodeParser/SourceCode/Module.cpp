#include "Module.h"

ModuleMode ModuleModeFromString(const std::string& InModeStr)
{
	if(InModeStr == "EXE")
	{
		return ModuleMode::EXE;
	}
	else if(InModeStr == "STATIC")
	{
		return ModuleMode::STATIC;
	}
	else if(InModeStr == "SHARED")
	{
		return ModuleMode::SHARED;
	}
	else if(InModeStr == "INTERFACE")
	{
		return ModuleMode::INTERFACE;
	}
	else if(InModeStr == "STATIC_AND_SHARED")
	{
		return ModuleMode::STATIC_AND_SHARED;
	}
	return ModuleMode::NONE;
}

ModuleOption OptionFromString(const AString& InOptionStr)
{
	ModuleOption Option;
	auto Strs = StringEx::Split(InOptionStr, "=");
	Option.OptionName = Strs[0];
	if(Strs.size() > 1)
	{
		Option.OptionValue = Strs[1];
	}
	return Option;
}

ModuleDefine DefineFromString(const AString& InDefineStr)
{
	ModuleDefine Define;
	auto Strs = StringEx::Split(InDefineStr, "=");
	Define.DefineName = Strs[0];
	if (Strs.size() > 1)
	{
		Define.DefineValue = Strs[1];
	}
	return Define;
}
