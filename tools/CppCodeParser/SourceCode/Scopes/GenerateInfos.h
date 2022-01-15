#pragma once

#include "CommonHeader.h"

struct ClassGenerateInfo
{
	AString ClassName;
};

struct EnumGenerateInfo
{
	AString Name;
};

struct EnumValueGenerateInfo
{
	AString Name;
};

struct FunctionGenerateInfo
{
	AString FunctionName;
};

struct NamespaceGenerateInfo
{
	AString NamespaceName;
};

struct FieldGenerateInfo
{
	AString FieldName;
};