#pragma once
#include "BaseScope.h"



class FunctionScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(FunctionScope, BaseScope)
	DEFINE_TO_JSON_MEMBER()
public:
	FunctionScope(const AString& InName = "")
		: BaseScope(InName)
	{
	}
	
};

