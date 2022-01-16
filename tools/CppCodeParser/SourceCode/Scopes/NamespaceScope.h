#pragma once
#include "BaseScope.h"


class NamespaceScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(NamespaceScope, BaseScope)
public:
	explicit NamespaceScope(const AString& InName = "")
		: BaseScope(InName)
	{
	}

	void AddNamespace(SharedPtr<NamespaceGenerateInfo> InNamespace) override;
	void AddClass(SharedPtr<ClassGenerateInfo> InClass) override;
	void AddMethod(SharedPtr<FunctionGenerateInfo> InMethodInfo) override;
	void AddField(SharedPtr<FieldGenerateInfo> InFieldInfo) override;
	void AddEnum(SharedPtr<EnumGenerateInfo> InEnumType) override;

	

private:
	Vector<SharedPtr<NamespaceGenerateInfo>> Namespaces;
	Vector<SharedPtr<ClassGenerateInfo>> GlobalClasses;
	Vector<SharedPtr<FieldGenerateInfo>> GlobalFields;
	Vector<SharedPtr<FunctionGenerateInfo>> GlobalMethods;
	Vector<SharedPtr<EnumGenerateInfo>> GlobalEnumTypes;

public:
	DEFINE_GETTER_DECLTYPE(Namespaces)
	DEFINE_GETTER_DECLTYPE(GlobalClasses)
	DEFINE_GETTER_DECLTYPE(GlobalFields)
	DEFINE_GETTER_DECLTYPE(GlobalMethods)
	DEFINE_GETTER_DECLTYPE(GlobalEnumTypes)
};

BEGIN_TO_JSON(NamespaceScope)
BASE_TO_JSON(BaseScope)
TO_JSON_ARG_WITH_GETTER(Namespaces)
TO_JSON_ARG_WITH_GETTER(GlobalClasses)
TO_JSON_ARG_WITH_GETTER(GlobalFields)
TO_JSON_ARG_WITH_GETTER(GlobalMethods)
TO_JSON_ARG_WITH_GETTER(GlobalEnumTypes)
END_TO_JSON()