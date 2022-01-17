#pragma once

#include "CommonHeader.h"
#include "GenerateInfos.h"

enum class ScopeType
{
	None,
	Global,
	Namespace,
	Enum,
	Function,
	Class
};

class BaseParser;
class CppFileParser;
class CppSourceFile;
class CppToken;

class BaseScope
{
	DEFINE_CLASS(BaseScope)
	DEFINE_TO_JSON_MEMBER()
public:

	BaseScope(const AString& InName = "") : Name(InName)
	{
		
	}

	const AString& GetName() const
	{
		return Name;
	}

	virtual ~BaseScope() = default;

	virtual void AddNamespace(SharedPtr<NamespaceGenerateInfo> InSpaceName)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Namespace");
	}

	virtual void AddClass(SharedPtr<ClassGenerateInfo> InClass)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Class");
	}

	virtual void AddMethod(SharedPtr<FunctionGenerateInfo> InMethodInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add MethodInfo");
	}

	virtual void AddField(SharedPtr<FieldGenerateInfo> InFieldInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add FieldInfo");
	}

	virtual void AddEnum(SharedPtr<EnumGenerateInfo> InEnumType)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add EnumType");
	}

	virtual bool CompileCurrentScope(CppFileParser& Parser, CppSourceFile& File, SharedPtr<CppToken> Token) { return false; }


protected:
	AString Name;

};


