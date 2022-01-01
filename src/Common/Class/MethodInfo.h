#pragma once

#include "FieldInfo.h"


class MethodInfo : public MemberInfo
{
public:

	MethodInfo(std::string InMethodName
		, MemberAccessType InMemberAccessType
		, MemberFlag InMemberFlag
		, MemberOwnerType InOwnerType
		, FieldInfo InReturnParam
		, std::vector<FieldInfo> InMethodParamInfos)
		: MemberInfo(std::move(InMethodName)
			, InMemberAccessType
			, InMemberFlag
			, InOwnerType)
		, ReturnField(std::move(InReturnParam))
		, MethodParamInfos(std::move(InMethodParamInfos))
	{
	}

	const FieldInfo& GetReturnParam() const
	{
		return ReturnField;
	}

	const std::vector<FieldInfo>& GetMethodParamInfos() const
	{
		return MethodParamInfos;
	}

	bool IsMethod() override
	{
		return true;
	}

private:
	const FieldInfo ReturnField;
	const std::vector<FieldInfo> MethodParamInfos;
};