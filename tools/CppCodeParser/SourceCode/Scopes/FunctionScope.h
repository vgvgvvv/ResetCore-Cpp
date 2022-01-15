#pragma once
#include "BaseScope.h"



class FunctionScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(FunctionScope, BaseScope)
public:
	explicit FunctionScope(const AString& InName = "")
		: BaseScope(InName)
	{
	}
	
};
