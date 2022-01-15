#include "GlobalScope.h"

DEFINE_DERIVED_CLASS_IMP(GlobalScope, BaseScope)

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
