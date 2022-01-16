#pragma once

#include "CommonHeader.h"

struct AttributeInfo
{
	Vector<AString> AttrArr;
};

struct ClassGenerateInfo
{
	AString ClassName;
	SharedPtr<ClassScope> Scope;
};

struct EnumGenerateInfo
{
	AString Name;
	bool IsClassEnum;
	AttributeInfo AttrInfo;
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
	bool IsConst;
};

struct FunctionReturnParamGenerateInfo
{
	AString TypeName;
	bool IsConst;
};

struct FunctionGenerateInfo
{
	AString FunctionName;
	MemberFlag Flag;
	MemberAccessType AccessType;
	MemberOwnerType OwnerType;

	FunctionReturnParamGenerateInfo ReturnTypeName;
	Vector<FunctionParamGenerateInfo> ParamTypeNames;

	AttributeInfo AttrInfo;
	SharedPtr<FunctionScope> Scope;
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
	AttributeInfo AttrInfo;
};