#pragma once

#include "CommonHeader.h"
#include "Json/JsonSerialization.h"

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

	virtual void AddNamespace(SharedPtr<struct NamespaceGenerateInfo> InSpaceName)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Namespace");
	}

	virtual void AddClass(SharedPtr<struct ClassGenerateInfo> InClass)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add Class");
	}

	virtual void AddMethod(SharedPtr<struct FunctionGenerateInfo> InMethodInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add MethodInfo");
	}

	virtual void AddField(SharedPtr<struct FieldGenerateInfo> InFieldInfo)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add FieldInfo");
	}

	virtual void AddEnum(SharedPtr<struct EnumGenerateInfo> InEnumType)
	{
		RE_ASSERT_MSG(false, "Current Scope Not Support Add EnumType");
	}

	virtual bool CompileCurrentScope(CppFileParser& Parser, CppSourceFile& File, SharedPtr<CppToken> Token) { return false; }


protected:
	AString Name;

};


BEGIN_TO_JSON(BaseScope)
Result["Class"] = Obj.GetClass()->Name();
Result["Name"] = Obj.GetName();
END_TO_JSON()