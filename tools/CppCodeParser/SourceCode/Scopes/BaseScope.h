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

	virtual void AddNamespace()
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Namespace");
	}

	virtual void AddClass()
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Class");
	}

	virtual void AddFunction()
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Function");
	}

	virtual void AddMember()
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Member");
	}

};