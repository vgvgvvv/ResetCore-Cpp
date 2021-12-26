#include "Token.h"
#include "CommonHeader.h"


DEFINE_CLASS_IMP(CppToken)

void CppToken::InitToken()
{
	TokenType = CppTokenType::None;
	StartPos = 0;
	StartLine = 0;
	*Identifier = 0;
	MemoryLibrary::Memzero(String);
}

AString CppToken::GetTokenName() const
{
	return std::string(Identifier);
}

AString CppToken::GetConstantValue() const
{
	if(TokenType == CppTokenType::Const)
	{
		switch (ConstType)
		{
		case CppTokenConstType::Byte: 
			return fmt::format("{0}", Byte);
		case CppTokenConstType::Int: 
			return fmt::format("{0}", Int);
		case CppTokenConstType::Int64:
			return fmt::format("{0}", Int64);
		case CppTokenConstType::Bool: 
			return fmt::format("{0}", NativeBool);
		case CppTokenConstType::Float: 
			return fmt::format("{0}", Float);
		case CppTokenConstType::Double: 
			return fmt::format("{0}", Double);
		case CppTokenConstType::String: 
			return fmt::format("{0}", String);
		default: 
			return "InvalidTypeForToken";
		}
	}
	return "NotConstant";
}
