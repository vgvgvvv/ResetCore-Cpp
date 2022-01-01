#pragma once

#include "CommonHeader.h"

enum class ScopeType
{
	None,
	Global,
	Namespace,
	Enum,
	Function,
	Class
};

class BaseScope
{
	DEFINE_CLASS(BaseScope)
public:

	virtual ~BaseScope() = default;

	virtual void AddNamespace(SharedPtr<Namespace> InSpaceName)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Namespace");
	}

	virtual void AddClass(SharedPtr<Class> InClass)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Class");
	}

	virtual void AddMethod(SharedPtr<MethodInfo> InMethodInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add MethodInfo");
	}

	virtual void AddField(SharedPtr<FieldInfo> InFieldInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add FieldInfo");
	}

	virtual void AddEnum(SharedPtr<EnumType> InEnumType)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add EnumType");
	}

};