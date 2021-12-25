#pragma once

#include "CppCodeParser_API.h"
#include "CommonHeader.h"
#include "CppSourceFile.h"


enum class ModuleMode
{
	NONE = 0,
	EXE,
	STATIC,
	SHARED,
	INTERFACE,
	STATIC_AND_SHARED,
	MAX = STATIC_AND_SHARED
};

CppCodeParser_API ModuleMode ModuleModeFromString(const String& InModeStr);

struct ModuleOption
{
	std::string OptionName;
	std::string OptionValue;
};

ModuleOption OptionFromString(const String& InOptionStr);

struct ModuleDefine
{
	std::string DefineName;
	std::string DefineValue;
	
};

ModuleDefine DefineFromString(const String& InDefineStr);

struct CppCodeParser_API CppModule
{
	std::string TargetName;
	ModuleMode ModuleType;

	std::vector<CppSourceFile> PublicIncludeFiles;
	std::vector<CppSourceFile> InterfaceIncludeFiles;
	std::vector<CppSourceFile> PrivateIncludeFiles;

	std::vector<CppSourceFile> PublicSourceFiles;
	std::vector<CppSourceFile> InterfaceSourceFiles;
	std::vector<CppSourceFile> PrivateSourceFiles;

	std::vector<CppSourceFile> PublicPCHFiles;
	std::vector<CppSourceFile> InterfacePCHFiles;
	std::vector<CppSourceFile> PrivatePCHFiles;

	std::vector<ModuleOption> PublicCompileOptions;
	std::vector<ModuleOption> InterfaceCompileOptions;
	std::vector<ModuleOption> PrivateCompileOptions;

	std::vector<ModuleOption> PublicLinkOptions;
	std::vector<ModuleOption> InterfaceLinkOptions;
	std::vector<ModuleOption> PrivateLinkOptions;

	std::vector<CppModule> PublicLib;
	std::vector<CppModule> InterfaceLib;
	std::vector<CppModule> PrivateLib;

	std::vector<ModuleDefine> PublicDefine;
	std::vector<ModuleDefine> InterfaceDefine;
	std::vector<ModuleDefine> PrivateDefine;

	std::vector<ModuleOption> AddOptions;
};