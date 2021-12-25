#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"

struct CppModule;

class CppCodeParser_API CppProject
{
public:
	
	/**
	 * \brief Load Project Form Path
	 * \param RootPath 
	 */
	void Load(const std::string& RootPath);

private:

	void AddModuleToCppModule(const DirectoryEntry& FilePath);

private:

	Map<String, std::shared_ptr<CppModule>> ModuleCache;
};
