#pragma once
#include "CommonHeader.h"
#include "Class/Class.h"
#include "CppCodeParser_API.h"


enum class CppTokenType
{
	None = 0,
	Identifier,
	Symbol,
	Const,
	Max
};

enum class CppTokenConstType
{
	None,
	Byte,
	Int,
	Int64,
	Bool,
	Float,
	Double,
	String
};

class CppCodeParser_API CppToken
{
	DEFINE_CLASS(CppToken)

	friend class BaseParser;

public:
	enum { NAME_SIZE = 1024 };
	enum { MAX_STRING_CONST_SIZE = 1024 };

private:
	// Token Type
	CppTokenType TokenType = CppTokenType::None;

	// Token Position
	int32 StartPos = 0;
	int32 StartLine = 1;
	// Token Identifier String
	TCHAR Identifier[NAME_SIZE];

public:
	// Storage for Const
	CppTokenConstType ConstType = CppTokenConstType::None;
	union
	{
		// TOKEN_Const values.
		uint8 Byte;								// If CPT_Byte.
		int64 Int64;							// If CPT_Int64.
		int32 Int;								// If CPT_Int.
		bool NativeBool;						// if CPT_Bool
		float Float;							// If CPT_Float.
		double Double;							// If CPT_Double.
		TCHAR String[MAX_STRING_CONST_SIZE];	// If CPT_String
	};

public:

	void InitToken();

	// GetName
	AString GetTokenName() const;

	const TCHAR* GetRawTokenName() const;

	AString GetConstantValue() const;

	CppTokenType GetTokenType() const
	{
		return TokenType;
	}

	CppTokenConstType GetConstType() const
	{
		return ConstType;
	}

	// match
	bool Matches(const char Ch) const
	{
		return TokenType == CppTokenType::Symbol && Identifier[0] == Ch && Identifier[1] == 0;
	}

	bool Matches(const char* Str) const
	{
		return (TokenType == CppTokenType::Identifier || TokenType == CppTokenType::Symbol) && StringEx::Strcmp(Identifier, Str) == 0;
	}

	bool IsBool() const
	{
		return ConstType == CppTokenConstType::Bool;
	}

#pragma region setters

	// setter
	void SetIdentifier(const char* InString)
	{
		InitToken();
		TokenType = CppTokenType::Identifier;
		StringEx::Strncpy(Identifier, InString, NAME_SIZE);
	}

	void SetConstInt64(int64 InInt64)
	{
		ConstType = CppTokenConstType::Int64;
		TokenType = CppTokenType::Const;
		Int64 = InInt64;
	}

	void SetConstInt(int32 InInt)
	{
		ConstType = CppTokenConstType::Int;
		TokenType = CppTokenType::Const;
		Int = InInt;
	}

	void SetConstBool(bool InBool)
	{
		ConstType = CppTokenConstType::Bool;
		TokenType = CppTokenType::Const;
		NativeBool = InBool;
	}

	void SetConstFloat(float InFloat)
	{
		ConstType = CppTokenConstType::Float;
		TokenType = CppTokenType::Const;
		Float = InFloat;
	}

	void SetConstDouble(double InDouble)
	{
		ConstType = CppTokenConstType::Double;
		TokenType = CppTokenType::Const;
		Double = InDouble;
	}

	void SetConstString(const char* InString, int32 MaxLength = MAX_STRING_CONST_SIZE)
	{
		RE_ASSERT(MaxLength > 0)
		ConstType = CppTokenConstType::String;
		TokenType = CppTokenType::Const;
		if(InString != String)
		{
			StringEx::Strncpy(String, InString, MaxLength);
		}
	}

	void SetConstChar(char InChar)
	{
		String[0] = InChar;
		String[1] = 0;
		TokenType = CppTokenType::Const;
	}

#pragma endregion

#pragma region getter

	bool GetConstInt(int32& OutInt) const
	{
		if(TokenType == CppTokenType::Const)
		{
			if(ConstType == CppTokenConstType::Int64)
			{
				OutInt = static_cast<int32>(Int64);
				return true;
			}
			else if(ConstType == CppTokenConstType::Int)
			{
				OutInt = Int;
				return true;
			}
			else if(ConstType == CppTokenConstType::Byte)
			{
				OutInt = Byte;
				return true;
			}
			else if(ConstType == CppTokenConstType::Float)
			{
				OutInt = static_cast<int32>(Float);
				return true;
			}
			else if(ConstType == CppTokenConstType::Double)
			{
				OutInt = static_cast<int32>(Double);
				return true;
			}
			else if (ConstType == CppTokenConstType::Bool)
			{
				OutInt = NativeBool ? 1 : 0;
				return true;
			}
		}
		return false;
	}

	bool GetConstInt64(int64& OutInt) const
	{
		if (TokenType == CppTokenType::Const)
		{
			if (ConstType == CppTokenConstType::Int64)
			{
				OutInt = Int64;
				return true;
			}
			else if (ConstType == CppTokenConstType::Int)
			{
				OutInt = Int;
				return true;
			}
			else if (ConstType == CppTokenConstType::Byte)
			{
				OutInt = Byte;
				return true;
			}
			else if (ConstType == CppTokenConstType::Float)
			{
				OutInt = static_cast<int64>(Float);
				return true;
			}
			else if (ConstType == CppTokenConstType::Double)
			{
				OutInt = static_cast<int64>(Double);
				return true;
			}
			else if (ConstType == CppTokenConstType::Bool)
			{
				OutInt = NativeBool ? 1 : 0;
				return true;
			}
		}
		return false;
	}

	bool GetBool(bool& OutBool) const
	{
		if (TokenType == CppTokenType::Const)
		{
			if (ConstType == CppTokenConstType::Int64)
			{
				OutBool = Int64 != 0;
				return true;
			}
			else if (ConstType == CppTokenConstType::Int)
			{
				OutBool = Int != 0;
				return true;
			}
			else if (ConstType == CppTokenConstType::Byte)
			{
				OutBool = Byte != 0;
				return true;
			}
			else if (ConstType == CppTokenConstType::Float)
			{
				OutBool = Float != 0;
				return true;
			}
			else if (ConstType == CppTokenConstType::Double)
			{
				OutBool = Double != 0;
				return true;
			}
			else if (ConstType == CppTokenConstType::Bool)
			{
				OutBool = NativeBool;
				return true;
			}
		}
		return false;
	}

#pragma endregion
};
