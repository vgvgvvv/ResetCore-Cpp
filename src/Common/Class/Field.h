#pragma once
#include "Class.h"


class Fieldinfo
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