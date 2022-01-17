#include "GenerateInfos.h"
#include "NamespaceScope.h"
#include "ClassScope.h"
#include "EnumScope.h"
#include "FunctionScope.h"
#include "Json/JsonSerialization.h"

DEFINE_CLASS_IMP(AttributeInfo)
BEGIN_TO_JSON_MEMBER_IMP(AttributeInfo)
TO_JSON_ARG(AttrArr)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(ClassGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(ClassGenerateInfo)
TO_JSON_ARG(GenerateClassName)
TO_JSON_ARG(Scope)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(EnumGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(EnumGenerateInfo)
TO_JSON_ARG(Name)
TO_JSON_ARG(IsClassEnum)
TO_JSON_ARG(AttrInfo)
TO_JSON_ARG(Scope)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(EnumValueGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(EnumValueGenerateInfo)
TO_JSON_ARG(Name)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(FunctionParamGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(FunctionParamGenerateInfo)
TO_JSON_ARG(Name)
TO_JSON_ARG(TypeName)
TO_JSON_ARG(IsConst)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(FunctionReturnParamGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(FunctionReturnParamGenerateInfo)
TO_JSON_ARG(TypeName)
TO_JSON_ARG(IsConst)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(FunctionGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(FunctionGenerateInfo)
TO_JSON_ARG(FunctionName)
TO_JSON_ARG(Flag)
TO_JSON_ARG(AccessType)
TO_JSON_ARG(OwnerType)
TO_JSON_ARG(ReturnTypeName)
TO_JSON_ARG(ParamTypeNames)
TO_JSON_ARG(AttrInfo)
TO_JSON_ARG(Scope)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(NamespaceGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(NamespaceGenerateInfo)
TO_JSON_ARG(NamespaceName)
TO_JSON_ARG(Scope)
END_TO_JSON_MEMBER_IMP()

DEFINE_CLASS_IMP(FieldGenerateInfo)
BEGIN_TO_JSON_MEMBER_IMP(FieldGenerateInfo)
TO_JSON_ARG(FieldName)
TO_JSON_ARG(TypeName)
TO_JSON_ARG(AccessType)
TO_JSON_ARG(Flag)
TO_JSON_ARG(OwnerType)
TO_JSON_ARG(AttrInfo)
END_TO_JSON_MEMBER_IMP()
