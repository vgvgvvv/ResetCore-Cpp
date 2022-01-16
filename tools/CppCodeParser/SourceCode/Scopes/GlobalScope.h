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
private:
	Vector<SharedPtr<NamespaceGenerateInfo>> Namespaces;
	Vector<SharedPtr<ClassGenerateInfo>> GlobalClasses;
	Vector<SharedPtr<FieldGenerateInfo>> GlobalFields;
	Vector<SharedPtr<FunctionGenerateInfo>> GlobalMethods;
	Vector<SharedPtr<EnumGenerateInfo>> GlobalEnumTypes;
};

template<>
nlohmann::json ToJson<GlobalScope>(const GlobalScope& Scope)
{
	
}