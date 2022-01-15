#pragma once

#include "BaseScope.h"


class ClassScope : public BaseScope
{
	DEFINE_DERIVED_CLASS(ClassScope, BaseScope)

public:
	explicit ClassScope(const AString& InName = "")
		: BaseScope(InName)
	{
	}

	void AddClass(SharedPtr<ClassGenerateInfo> InClass) override;
	void AddMethod(SharedPtr<FunctionGenerateInfo> InMethodInfo) override;
	void AddField(SharedPtr<FieldGenerateInfo> InFieldInfo) override;
	void AddEnum(SharedPtr<EnumGenerateInfo> InEnumType) override;

	MemberAccessType GetCurrentAccessType() const;
	bool CompileCurrentScope(CppFileParser& Parser, CppSourceFile& File, SharedPtr<CppToken> Token) override;

private:
	Vector<SharedPtr<ClassGenerateInfo>> InternalClasses;
	Vector<SharedPtr<FieldGenerateInfo>> MemberFields;
	Vector<SharedPtr<FunctionGenerateInfo>> MemberMehtods;
	Vector<SharedPtr<EnumGenerateInfo>> InternalEnumTypes;

	MemberAccessType CurrentMemberAccessType = MemberAccessType::Private;
};