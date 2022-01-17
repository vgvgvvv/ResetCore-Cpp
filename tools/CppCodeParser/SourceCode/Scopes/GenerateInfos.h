#pragma once

#include "CommonHeader.h"
#include "Json/ToJsonDefine.h"

struct AttributeInfo
{
	DEFINE_CLASS(AttributeInfo)
	DEFINE_TO_JSON_MEMBER()
public:

	Vector<AString> AttrArr;
};

struct ClassGenerateInfo
{
	DEFINE_CLASS(ClassGenerateInfo)
	DEFINE_TO_JSON_MEMBER()
public:

	AString GenerateClassName;
	SharedPtr<class ClassScope> Scope;
};

struct EnumGenerateInfo
{
	DEFINE_CLASS(EnumGenerateInfo)
	DEFINE_TO_JSON_MEMBER()
public:

	AString Name;
	bool IsClassEnum;
	AttributeInfo AttrInfo;
	SharedPtr<class EnumScope> Scope;
};

struct EnumValueGenerateInfo
{
	DEFINE_CLASS(EnumValueGenerateInfo)
	DEFINE_TO_JSON_MEMBER()
public:
	

	AString Name;
};

struct FunctionParamGenerateInfo
{
	DEFINE_CLASS(FunctionParamGenerateInfo)
	DEFINE_TO_JSON_MEMBER()
public:
	
	AString Name;
	AString TypeName;
	bool IsConst;
};

struct FunctionReturnParamGenerateInfo
{
	DEFINE_CLASS(FunctionReturnParamGenerateInfo)
	DEFINE_TO_JSON_MEMBER()
public:
	AString TypeName;
	bool IsConst;
};

struct FunctionGenerateInfo
{
	DEFINE_CLASS(FunctionGenerateInfo)
	DEFINE_TO_JSON_MEMBER()
public:

	AString FunctionName;
	MemberFlag Flag;
	MemberAccessType AccessType;
	MemberOwnerType OwnerType;

	FunctionReturnParamGenerateInfo ReturnTypeName;
	Vector<FunctionParamGenerateInfo> ParamTypeNames;

	AttributeInfo AttrInfo;
	SharedPtr<class FunctionScope> Scope;
};

struct NamespaceGenerateInfo
{
	DEFINE_CLASS(NamespaceGenerateInfo)
	DEFINE_TO_JSON_MEMBER()
public:

	AString NamespaceName;
	SharedPtr<class NamespaceScope> Scope;
};

struct FieldGenerateInfo
{
	DEFINE_CLASS(FieldGenerateInfo)
	DEFINE_TO_JSON_MEMBER()

public:

	AString FieldName;
	AString TypeName;
	MemberAccessType AccessType;
	MemberFlag Flag;
	MemberOwnerType OwnerType;
	AttributeInfo AttrInfo;
};
