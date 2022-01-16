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

BEGIN_TO_JSON(FunctionScope)
BASE_TO_JSON(BaseScope)
END_TO_JSON()