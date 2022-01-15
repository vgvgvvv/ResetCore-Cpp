#include "NamespaceScope.h"

DEFINE_DERIVED_CLASS_IMP(NamespaceScope, BaseScope)

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
