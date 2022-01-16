#pragma once

#include "CommonHeader.h"

struct AttributeInfo
{
	Vector<AString> AttrInfos;
};

struct ClassGenerateInfo
{
	AString ClassName;
};

struct EnumGenerateInfo
{
	AString Name;
	bool IsClassEnum;
	SharedPtr<EnumScope> Scope;
};

struct EnumValueGenerateInfo
{
	AString Name;
};

struct FunctionParamGenerateInfo
{
	AString Name;
	AString TypeName;
};

struct FunctionGenerateInfo
{
	AString FunctionName;
	FunctionParamGenerateInfo ReturnType;
	Vector<FunctionParamGenerateInfo> ParamTypes;
};

struct NamespaceGenerateInfo
{
	AString NamespaceName;
};

struct FieldGenerateInfo
{
	AString FieldName;
	AString TypeName;
	MemberAccessType AccessType;
	MemberFlag Flag;
	MemberOwnerType OwnerType;
};