#include "Project.h"
#include "Module.h"
#include "nlohmann/json.hpp"
#include <fstream>


void CppProject::Load(const std::string& RootPath)
{
	if(!fs::exists(RootPath))
	{
		RE_LOG_ERROR("CppProject::Load", "Project Path {0} Not Exist!!", RootPath.c_str());
		return;
	}
	Vector<DirectoryEntry> TargetJsons;
	CommonLib::GetFilesWithCondition(RootPath, TargetJsons, [](const DirectoryEntry& entry) -> bool
		{
			bool Valid = entry.path().string().ends_with(".Target.json");
			return Valid;
		}, false);

	for (DirectoryEntry& JsonFile : TargetJsons)
	{
		AddModuleToCppModule(JsonFile);
	}
}

void CppProject::AddModuleToCppModule(const DirectoryEntry& FileEntry)
{
    auto FilePath = FileEntry.path().c_str();
	RE_LOG_INFO("CppProject::AddModuleToCppModule", "Load Module File : {0}", FileEntry.path().filename().string().c_str())
	auto Module = std::make_shared<CppModule>();

	std::ifstream inputFile(FilePath);
	nlohmann::json doc;

	doc << inputFile;

    Module->TargetName = doc["targetName"].get<std::string>();

    auto ModeStr = doc["mode"].get<std::string>();
    Module->ModuleType = ModuleModeFromString(ModeStr);

    if(Module->ModuleType == ModuleMode::NONE)
    {
        RE_LOG_ERROR("CppProject::AddModuleToCppModule", "Load Module File Error, Mode String Is Invalid {0}", ModeStr.c_str())
        return;
    }

    for (const auto &item : doc["public_include"])
    {
        auto FileName = item.get<std::string>();
        Module->PublicIncludeFiles.emplace_back(std::move(FileName));
    }
    for (const auto &item : doc["interface_include"])
    {
        auto FileName = item.get<std::string>();
        Module->InterfaceIncludeFiles.emplace_back(std::move(FileName));
    }
    for (const auto &item : doc["private_include"])
    {
        auto FileName = item.get<std::string>();
        Module->PrivateIncludeFiles.emplace_back(std::move(FileName));
    }

    for (const auto &item : doc["public_source"])
    {
        auto FileName = item.get<std::string>();
        Module->PublicSourceFiles.emplace_back(std::move(FileName));
    }
    for (const auto &item : doc["interface_source"])
    {
        auto FileName = item.get<std::string>();
        Module->InterfaceSourceFiles.emplace_back(std::move(FileName));
    }
    for (const auto &item : doc["private_source"])
    {
        auto FileName = item.get<std::string>();
        Module->PrivateSourceFiles.emplace_back(std::move(FileName));
    }

    for (const auto& item : doc["public_compile_option"])
    {
        auto OptionStr = item.get<std::string>();
        Module->PublicCompileOptions.emplace_back(OptionFromString(OptionStr));
    }
    for (const auto& item : doc["interface_compile_option"])
    {
        auto OptionStr = item.get<std::string>();
        Module->InterfaceCompileOptions.emplace_back(OptionFromString(OptionStr));
    }
    for (const auto& item : doc["private_compile_option"])
    {
        auto OptionStr = item.get<std::string>();
        Module->PrivateCompileOptions.emplace_back(OptionFromString(OptionStr));
    }

    for (const auto& item : doc["public_link_option"])
    {
        auto OptionStr = item.get<std::string>();
        Module->PublicLinkOptions.emplace_back(OptionFromString(OptionStr));
    }
    for (const auto& item : doc["interface_link_option"])
    {
        auto OptionStr = item.get<std::string>();
        Module->InterfaceLinkOptions.emplace_back(OptionFromString(OptionStr));
    }
    for (const auto& item : doc["private_link_option"])
    {
        auto OptionStr = item.get<std::string>();
        Module->PrivateLinkOptions.emplace_back(OptionFromString(OptionStr));
    }

    for (const auto& item : doc["public_pch"])
    {
        auto FileName = item.get<std::string>();
        Module->PublicPCHFiles.emplace_back(std::move(FileName));
    }
    for (const auto& item : doc["interface_pch"])
    {
        auto FileName = item.get<std::string>();
        Module->InterfacePCHFiles.emplace_back(std::move(FileName));
    }
    for (const auto& item : doc["private_pch"])
    {
        auto FileName = item.get<std::string>();
        Module->PrivatePCHFiles.emplace_back(std::move(FileName));
    }

    for (const auto& item : doc["public_lib"])
    {
        auto FileName = item.get<std::string>();
        Module->PublicLib.emplace_back(std::move(FileName));
    }
    for (const auto& item : doc["interface_lib"])
    {
        auto FileName = item.get<std::string>();
        Module->InterfaceLib.emplace_back(std::move(FileName));
    }
    for (const auto& item : doc["private_lib"])
    {
        auto FileName = item.get<std::string>();
        Module->PrivateLib.emplace_back(std::move(FileName));
    }

    for (const auto& item : doc["public_define"])
    {
        auto OptionStr = item.get<std::string>();
        Module->PublicDefine.emplace_back(DefineFromString(OptionStr));
    }
    for (const auto& item : doc["interface_define"])
    {
        auto OptionStr = item.get<std::string>();
        Module->InterfaceDefine.emplace_back(DefineFromString(OptionStr));
    }
    for (const auto& item : doc["private_define"])
    {
        auto OptionStr = item.get<std::string>();
        Module->PrivateDefine.emplace_back(DefineFromString(OptionStr));
    }

    for (const auto& item : doc["add_options"])
    {
        auto OptionStr = item.get<std::string>();
        Module->AddOptions.emplace_back(OptionFromString(OptionStr));
    }

	inputFile.close();

	ModuleCache.insert(std::make_pair(Module->TargetName, Module));
}
