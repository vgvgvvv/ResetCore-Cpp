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

private:
	Type* FieldType = nullptr;
	const char* FieldName = nullptr;
	FieldOwnerType OwnerType = FieldOwnerType::None;
};