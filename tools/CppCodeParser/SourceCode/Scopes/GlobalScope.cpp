#include "GlobalScope.h"
#include "Json/JsonSerialization.h"

DEFINE_DERIVED_CLASS_IMP(GlobalScope, BaseScope)
BEGIN_TO_JSON(GlobalScope)
BASE_TO_JSON(BaseScope)
TO_JSON_ARG_WITH_GETTER(Namespaces)
TO_JSON_ARG_WITH_GETTER(GlobalClasses)
TO_JSON_ARG_WITH_GETTER(GlobalFields)
TO_JSON_ARG_WITH_GETTER(GlobalMethods)
TO_JSON_ARG_WITH_GETTER(GlobalEnumTypes)
END_TO_JSON()
DEFINE_TO_JSON_MEMBER_IMP(GlobalScope)

void GlobalScope::AddNamespace(SharedPtr<NamespaceGenerateInfo> InSpaceName)
{
	Namespaces.push_back(InSpaceName);
}

void GlobalScope::AddClass(SharedPtr<ClassGenerateInfo> InClass)
{
	GlobalClasses.push_back(InClass);
}

void GlobalScope::AddMethod(SharedPtr<FunctionGenerateInfo> InMethodInfo)
{
	GlobalMethods.push_back(InMethodInfo);
}

void GlobalScope::AddField(SharedPtr<FieldGenerateInfo> InFieldInfo)
{
	GlobalFields.push_back(InFieldInfo);
}

void GlobalScope::AddEnum(SharedPtr<EnumGenerateInfo> InEnumType)
{
	GlobalEnumTypes.push_back(InEnumType);
}
