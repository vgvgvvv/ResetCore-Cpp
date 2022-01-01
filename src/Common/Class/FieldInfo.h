#pragma once
#include "Class.h"


class FieldInfo
{
public:

	enum class FieldOwnerType
	{
		None,
		ClassMember,
		Global
	};

	FieldInfo(const Type* InFieldType,
	          std::string InFieldName, 
		FieldOwnerType InOwnerType)
		: FieldType(InFieldType)
		, FieldName(std::move(InFieldName))
		, OwnerType(InOwnerType)
	{
	}

	const Type* GetFieldType() const
	{
		return FieldType;
	}

	const std::string& GetName() const
	{
		return FieldName;
	}

	const FieldOwnerType GetOwnerType() const
	{
		return OwnerType;
	}

private:
	const Type* FieldType = nullptr;
	const std::string FieldName;
	const FieldOwnerType OwnerType = FieldOwnerType::None;
};