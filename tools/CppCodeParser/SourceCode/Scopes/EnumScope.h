#pragma once
#include "BaseScope.h"

struct EnumValueGenerateInfo;

class EnumScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(EnumScope, BaseScope)
	DEFINE_TO_JSON_MEMBER()
public:
	EnumScope(const AString& InName = "")
		: BaseScope(InName)
	{
	}

	Vector<SharedPtr<EnumValueGenerateInfo>>& GetFieldInfos()
	{
		return FieldInfos;
	}

	DEFINE_GETTER(Vector<SharedPtr<EnumValueGenerateInfo>>, FieldInfos)

private:
	Vector<SharedPtr<EnumValueGenerateInfo>> FieldInfos;
};

