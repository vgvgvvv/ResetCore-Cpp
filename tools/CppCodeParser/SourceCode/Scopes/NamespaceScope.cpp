#include "NamespaceScope.h"
#include "Json/JsonSerialization.h"

DEFINE_DERIVED_CLASS_IMP(NamespaceScope, BaseScope)
BEGIN_TO_JSON_MEMBER_IMP(NamespaceScope)
BASE_TO_JSON(BaseScope)
TO_JSON_ARG_WITH_GETTER(Namespaces)
TO_JSON_ARG_WITH_GETTER(GlobalClasses)
TO_JSON_ARG_WITH_GETTER(GlobalFields)
TO_JSON_ARG_WITH_GETTER(GlobalMethods)
TO_JSON_ARG_WITH_GETTER(GlobalEnumTypes)
END_TO_JSON_MEMBER_IMP()

void NamespaceScope::AddNamespace(SharedPtr<NamespaceGenerateInfo> InNamespace)
{
	Namespaces.push_back(InNamespace);
}

void NamespaceScope::AddClass(SharedPtr<ClassGenerateInfo> InClass)
{
	GlobalClasses.push_back(InClass);
}

void NamespaceScope::AddMethod(SharedPtr<FunctionGenerateInfo> InMethodInfo)
{
	GlobalMethods.push_back(InMethodInfo);
}

void NamespaceScope::AddField(SharedPtr<FieldGenerateInfo> InFieldInfo)
{
	GlobalFields.push_back(InFieldInfo);
}

void NamespaceScope::AddEnum(SharedPtr<EnumGenerateInfo> InEnumType)
{
	GlobalEnumTypes.push_back(InEnumType);
}
