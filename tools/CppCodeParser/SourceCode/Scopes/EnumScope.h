#pragma once
#include "BaseScope.h"

struct EnumValueGenerateInfo;

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

	DEFINE_GETTER(Vector<SharedPtr<EnumValueGenerateInfo>>, FieldInfos)

private:
	Vector<SharedPtr<EnumValueGenerateInfo>> FieldInfos;
};

BEGIN_TO_JSON(EnumScope)
BASE_TO_JSON(BaseScope)
TO_JSON_ARG_WITH_GETTER(FieldInfos)
END_TO_JSON()
