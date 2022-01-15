#pragma once
#include "BaseScope.h"

class EnumValueGenerateInfo;

class EnumScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(EnumScope, BaseScope)
public:
	explicit EnumScope(const AString& InName = "")
		: BaseScope(InName)
	{
	}

	Vector<SharedPtr<EnumValueGenerateInfo>>& GetFieldInfos()
	{
		return FieldInfos;
	}

private:
	Vector<SharedPtr<EnumValueGenerateInfo>> FieldInfos;
};
