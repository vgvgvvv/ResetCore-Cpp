#pragma once
#include "BaseScope.h"
#include "Json/ToJsonDefine.h"

class GlobalScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(GlobalScope, BaseScope)
	DEFINE_TO_JSON_MEMBER()
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

