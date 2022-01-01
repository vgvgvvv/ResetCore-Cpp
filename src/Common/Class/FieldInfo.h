#pragma once
#include "Class.h"
#include "MemberInfo.h"


enum class FieldOwnerType
{
	None,
	ClassMember,
	Global
};

class FieldInfo : public MemberInfo
{
public:

	FieldInfo(std::string InFieldName,
		MemberAccessType InMemberAccessType,
		MemberFlag InMemberFlag,
		const Type* InFieldType,
		FieldOwnerType InOwnerType)
		: MemberInfo(std::move(InFieldName), InMemberAccessType, InMemberFlag)
		, FieldType(InFieldType)
		, OwnerType(InOwnerType)
	{
	}

	const Type* GetFieldType() const
	{
		return FieldType;
	}

	const FieldOwnerType GetOwnerType() const
	{
		return OwnerType;
	}

	bool IsField() override
	{
		return true;
	}

private:
	const Type* FieldType = nullptr;
	const FieldOwnerType OwnerType = FieldOwnerType::None;
};