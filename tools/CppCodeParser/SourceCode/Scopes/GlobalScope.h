#pragma once
#include "BaseScope.h"
#include "Json/JsonSerialization.h"

class GlobalScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(GlobalScope, BaseScope)
public:

	explicit GlobalScope(const AString& InName = "Global")
		: BaseScope(InName)
	{
	}

	void AddNamespace(SharedPtr<NamespaceGenerateInfo> InSpaceName) override;
	void AddClass(SharedPtr<ClassGenerateInfo> InClass) override;
	void AddMethod(SharedPtr<FunctionGenerateInfo> InMethodInfo) override;
	void AddField(SharedPtr<FieldGenerateInfo> InFieldInfo) override;
	void AddEnum(SharedPtr<EnumGenerateInfo> InEnumType) override;

    DEFINE_GETTER(Vector<SharedPtr<NamespaceGenerateInfo>>, Namespaces)
    DEFINE_GETTER(Vector<SharedPtr<ClassGenerateInfo>>, GlobalClasses)
    DEFINE_GETTER(Vector<SharedPtr<FieldGenerateInfo>>, GlobalFields)
    DEFINE_GETTER(Vector<SharedPtr<FunctionGenerateInfo>>, GlobalMethods)
    DEFINE_GETTER(Vector<SharedPtr<EnumGenerateInfo>>, GlobalEnumTypes)

private:
	Vector<SharedPtr<NamespaceGenerateInfo>> Namespaces;
	Vector<SharedPtr<ClassGenerateInfo>> GlobalClasses;
	Vector<SharedPtr<FieldGenerateInfo>> GlobalFields;
	Vector<SharedPtr<FunctionGenerateInfo>> GlobalMethods;
	Vector<SharedPtr<EnumGenerateInfo>> GlobalEnumTypes;
};

BEGIN_TO_JSON(GlobalScope)
BASE_TO_JSON(BaseScope)
TO_JSON_ARG_WITH_GETTER(Namespaces)
TO_JSON_ARG_WITH_GETTER(GlobalClasses)
TO_JSON_ARG_WITH_GETTER(GlobalFields)
TO_JSON_ARG_WITH_GETTER(GlobalMethods)
TO_JSON_ARG_WITH_GETTER(GlobalEnumTypes)
END_TO_JSON()