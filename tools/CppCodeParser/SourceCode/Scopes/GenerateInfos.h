#pragma once

#include "CommonHeader.h"
#include "Json/JsonSerialization.h"

struct AttributeInfo
{
	Vector<AString> AttrArr;
};

BEGIN_TO_JSON(AttributeInfo)
    TO_JSON_ARG(AttrArr)
END_TO_JSON()

struct ClassGenerateInfo
{
	AString ClassName;
	SharedPtr<ClassScope> Scope;
};

BEGIN_TO_JSON(ClassGenerateInfo)
    TO_JSON_ARG(ClassName)
    TO_JSON_ARG(Scope)
END_TO_JSON()

struct EnumGenerateInfo
{
	AString Name;
	bool IsClassEnum;
	AttributeInfo AttrInfo;
	SharedPtr<EnumScope> Scope;
};

BEGIN_TO_JSON(EnumGenerateInfo)
    TO_JSON_ARG(Name)
    TO_JSON_ARG(IsClassEnum)
    TO_JSON_ARG(AttrInfo)
    TO_JSON_ARG(Scope)
END_TO_JSON()


struct EnumValueGenerateInfo
{
	AString Name;
};

BEGIN_TO_JSON(EnumValueGenerateInfo)
    TO_JSON_ARG(Name)
END_TO_JSON()

struct FunctionParamGenerateInfo
{
	AString Name;
	AString TypeName;
	bool IsConst;
};

BEGIN_TO_JSON(FunctionParamGenerateInfo)
    TO_JSON_ARG(Name)
    TO_JSON_ARG(TypeName)
    TO_JSON_ARG(IsConst)
END_TO_JSON()

struct FunctionReturnParamGenerateInfo
{
	AString TypeName;
	bool IsConst;
};

BEGIN_TO_JSON(FunctionReturnParamGenerateInfo)
    TO_JSON_ARG(TypeName)
    TO_JSON_ARG(IsConst)
END_TO_JSON()

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

BEGIN_TO_JSON(FunctionGenerateInfo)
    TO_JSON_ARG(FunctionName)
    TO_JSON_ARG(Flag)
    TO_JSON_ARG(AccessType)
    TO_JSON_ARG(OwnerType)
    TO_JSON_ARG(ReturnTypeName)
    TO_JSON_ARG(ParamTypeNames)
    TO_JSON_ARG(AttrInfo)
    TO_JSON_ARG(Scope)
END_TO_JSON()

struct NamespaceGenerateInfo
{
	AString NamespaceName;
};

BEGIN_TO_JSON(NamespaceGenerateInfo)
    TO_JSON_ARG(NamespaceName)
END_TO_JSON()

struct FieldGenerateInfo
{
	AString FieldName;
	AString TypeName;
	MemberAccessType AccessType;
	MemberFlag Flag;
	MemberOwnerType OwnerType;
	AttributeInfo AttrInfo;
};

BEGIN_TO_JSON(FieldGenerateInfo)
    TO_JSON_ARG(FieldName)
    TO_JSON_ARG(TypeName)
    TO_JSON_ARG(AccessType)
    TO_JSON_ARG(Flag)
    TO_JSON_ARG(OwnerType)
    TO_JSON_ARG(AttrInfo)
END_TO_JSON()
