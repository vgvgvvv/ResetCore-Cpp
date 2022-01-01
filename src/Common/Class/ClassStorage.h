#pragma once

#include "FieldInfo.h"
#include "MethodInfo.h"

class ClassStorage
{
public:

	ClassStorage(std::map<std::string, FieldInfo> InFieldInfos, 
		std::map<std::string, MethodInfo> InMethodInfos)
		: FieldInfos(std::move(InFieldInfos))
		, MethodInfos(std::move(InMethodInfos))
	{
	}

	const FieldInfo* GetField(const std::string& Name) const
	{
		auto Iter = FieldInfos.find(Name);
		if(Iter != FieldInfos.end())
		{
			return &Iter->second;
		}else
		{
			return nullptr;
		}
	}

	const MethodInfo* GetMethod(const std::string& Name) const
	{
		auto Iter = MethodInfos.find(Name);
		if (Iter != MethodInfos.end())
		{
			return &Iter->second;
		}
		else
		{
			return nullptr;
		}
	}

private:
	std::map<std::string, FieldInfo> FieldInfos;
	std::map<std::string, MethodInfo> MethodInfos;
};