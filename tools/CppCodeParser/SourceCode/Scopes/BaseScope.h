#pragma once

#include "CommonHeader.h"

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
public:

	BaseScope(const AString& InName = "") : Name(InName)
	{
		
	}

	const AString& GetName() const
	{
		return Name;
	}

	virtual ~BaseScope() = default;

	virtual void AddNamespace(SharedPtr<class NamespaceGenerateInfo> InSpaceName)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Namespace");
	}

	virtual void AddClass(SharedPtr<class ClassGenerateInfo> InClass)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Class");
	}

	virtual void AddMethod(SharedPtr<class FunctionGenerateInfo> InMethodInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add MethodInfo");
	}

	virtual void AddField(SharedPtr<class FieldGenerateInfo> InFieldInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add FieldInfo");
	}

	virtual void AddEnum(SharedPtr<class EnumGenerateInfo> InEnumType)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add EnumType");
	}

	virtual bool CompileCurrentScope(CppFileParser& Parser, CppSourceFile& File, SharedPtr<CppToken> Token) { return false; }


protected:
	AString Name;

};