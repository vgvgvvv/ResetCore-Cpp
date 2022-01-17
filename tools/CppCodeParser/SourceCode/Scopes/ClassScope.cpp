#include "ClassScope.h"

#include "FrontEnd/CppFileParser.h"
#include "FrontEnd/Token.h"
#include "Json/JsonSerialization.h"


DEFINE_DERIVED_CLASS_IMP(ClassScope, BaseScope)
BEGIN_TO_JSON(ClassScope)
BASE_TO_JSON(BaseScope)
TO_JSON_ARG_WITH_GETTER(InternalClasses)
TO_JSON_ARG_WITH_GETTER(MemberFields)
TO_JSON_ARG_WITH_GETTER(MemberMehtods)
TO_JSON_ARG_WITH_GETTER(InternalEnumTypes)
END_TO_JSON()
DEFINE_TO_JSON_MEMBER_IMP(ClassScope)

void ClassScope::AddClass(SharedPtr<ClassGenerateInfo> InClass)
{
	InternalClasses.push_back(InClass);
}

void ClassScope::AddMethod(SharedPtr<FunctionGenerateInfo> InMethodInfo)
{
	MemberMehtods.push_back(InMethodInfo);
}

void ClassScope::AddField(SharedPtr<FieldGenerateInfo> InFieldInfo)
{
	MemberFields.push_back(InFieldInfo);
}

void ClassScope::AddEnum(SharedPtr<EnumGenerateInfo> InEnumType)
{
	InternalEnumTypes.push_back(InEnumType);
}

MemberAccessType ClassScope::GetCurrentAccessType() const
{
	return CurrentMemberAccessType;
}

bool ClassScope::CompileCurrentScope(CppFileParser& Parser, CppSourceFile& File, SharedPtr<CppToken> Token)
{
	if(Token->Matches("public"))
	{
		Parser.RequireSymbol(':', Parser.GetFileLocation(File).c_str());
		CurrentMemberAccessType = MemberAccessType::Public;
	}

	if (Token->Matches("private"))
	{
		Parser.RequireSymbol(':', Parser.GetFileLocation(File).c_str());
		CurrentMemberAccessType = MemberAccessType::Private;
		return true;
	}

	if (Token->Matches("protected"))
	{
		Parser.RequireSymbol(':', Parser.GetFileLocation(File).c_str());
		CurrentMemberAccessType = MemberAccessType::Protected;
	}

	return true;
}
