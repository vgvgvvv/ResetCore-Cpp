#include "Directory.h"

namespace CommonLib
{
	void GetFiles(const std::string& Path, std::vector<fs::directory_entry>& OutFiles, bool OnlyTop)
	{
		if(!fs::exists(Path))
		{
			return;
		}
		for (const auto& entry : fs::directory_iterator(Path))
		{
			if(!entry.is_directory())
			{
				OutFiles.push_back(entry);
			}
			else
			{
				if(!OnlyTop)
				{
					GetFiles(entry.path().string(), OutFiles, OnlyTop);
				}
			}
		}
	}

	void GetFilesWithCondition(const std::string& Path, std::vector<fs::directory_entry>& OutFiles, std::function<bool(const fs::directory_entry&)> Condition,
		bool OnlyTop)
	{
		if (!fs::exists(Path))
		{
			return;
		}
		for (const auto& entry : fs::directory_iterator(Path))
		{
			if (!entry.is_directory())
			{
				if(Condition(entry))
				{
					OutFiles.push_back(entry);
				}
			}
			else
			{
				if (!OnlyTop)
				{
					GetFilesWithCondition(entry.path().string(), OutFiles, Condition, OnlyTop);
				}
			}
		}
	}

	void GetDirectories(const std::string& Path, std::vector<fs::directory_entry>& OutDirectories)
	{
		if (!fs::exists(Path))
		{
			return;
		}
		for (const auto& entry : fs::directory_iterator(Path))
		{
			if (entry.is_directory())
			{
				OutDirectories.push_back(entry);
			}
		}
	}
}
