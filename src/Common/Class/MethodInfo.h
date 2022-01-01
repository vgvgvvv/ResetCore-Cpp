#pragma once

#include "FieldInfo.h"


class MethodInfo
{
public:

	MethodInfo(std::string InMethodName,
	           FieldInfo InReturnParam, 
	           std::vector<FieldInfo> InMethodParamInfos)
		: MethodName(std::move(InMethodName))
		, ReturnField(std::move(InReturnParam))
		, MethodParamInfos(std::move(InMethodParamInfos))
	{
	}

	const std::string& GetName() const
	{
		return MethodName;
	}

	const FieldInfo& GetReturnParam() const
	{
		return ReturnField;
	}

	const std::vector<FieldInfo>& GetMethodParamInfos() const
	{
		return MethodParamInfos;
	}

private:
	const std::string MethodName;
	const FieldInfo ReturnField;
	const std::vector<FieldInfo> MethodParamInfos;
};