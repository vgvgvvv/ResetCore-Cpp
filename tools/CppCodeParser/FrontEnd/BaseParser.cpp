#include "BaseParser.h"

#include "Token.h"

DEFINE_CLASS_IMP(BaseParser)

void BaseParser::InitParserSource(const char* SourceBuffer)
{
	Input = SourceBuffer;
	InputLen = StringEx::StrLen(SourceBuffer);
	InputPos = 0;
	InputLine = 1;
	PrevPos = 0;
	PrevLine = 1;
}

#pragma region basic operation

TCHAR BaseParser::GetChar(bool bLiteral)
{
	bool bInsideComment = false;

	PrevPos = InputPos;
	PrevLine = InputLine;

Loop:
	const TCHAR c = Input[InputPos++];
	if (bInsideComment)
	{
		// Record the character as a comment.
		PrevComment += c;
	}

	if (c == '\n')
	{
		InputLine++;
	}
	else if (!bLiteral)
	{
		const TCHAR NextChar = PeekChar();
		if (c == '/' && NextChar == '*')
		{
			if (!bInsideComment)
			{
				ClearComment();
				// Record the slash and star.
				PrevComment += c;
				PrevComment += NextChar;
				bInsideComment = true;

				// Move past the star. Do it only when not in comment,
				// otherwise end of comment might be missed e.g.
				// /*/ Comment /*/
				// ~~~~~~~~~~~~~^ Will report second /* as beginning of comment
				// And throw error that end of file is found in comment.
				InputPos++;
			}

			goto Loop;
		}
		else if (c == '*' && NextChar == '/')
		{
			if (!bInsideComment)
			{
				ClearComment();
				RE_ASSERT_MSG(false, "Unexpected '*/' outside of comment")
			}

			/** Asterisk and slash always end comment. */
			bInsideComment = false;

			// Star already recorded; record the slash.
			PrevComment += Input[InputPos];

			InputPos++;
			goto Loop;
		}
	}

	if (bInsideComment)
	{
		if (c == 0)
		{
			ClearComment();
			RE_ASSERT_MSG(false, "End of class header encountered inside comment")
		}
		goto Loop;
	}
	return c;
}

TCHAR BaseParser::PeekChar()
{
	return (InputPos < InputLen) ? Input[InputPos] : 0;
}

TCHAR BaseParser::GetLeadingChar()
{
	TCHAR TrailingCommentNewline = 0;

	for (;;)
	{
		bool MultipleNewlines = false;

		TCHAR c;

		// Skip blanks.
		do
		{
			c = GetChar();

			// Check if we've encountered another newline since the last one
			if (c == TrailingCommentNewline)
			{
				MultipleNewlines = true;
			}
		} while (IsWhitespace(c));

		if (c != '/' || PeekChar() != '/')
		{
			return c;
		}

		// Clear the comment if we've encountered newlines since the last comment
		if (MultipleNewlines)
		{
			ClearComment();
		}

		// Record the first slash.  The first iteration of the loop will get the second slash.
		PrevComment += c;

		do
		{
			c = GetChar(true);
			if (c == 0)
				return c;
			PrevComment += c;
		} while (!IsEOL(c));

		TrailingCommentNewline = c;

		for (;;)
		{
			c = GetChar();
			if (c == 0)
				return c;
			if (c == TrailingCommentNewline || !IsEOL(c))
			{
				UngetChar();
				break;
			}

			PrevComment += c;
		}
	}
}

void BaseParser::UngetChar()
{
	InputPos = PrevPos;
	InputLine = PrevLine;
}

bool BaseParser::IsEOL(TCHAR c)
{
	return c == '\n' || c == '\r' || c == 0;
}

bool BaseParser::IsWhitespace(TCHAR c)
{
	return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

#pragma endregion

void BaseParser::ClearComment()
{
	PrevComment.clear();
}

SharedPtr<CppToken> BaseParser::GetToken(bool bNoConsts)
{
	TCHAR c = GetLeadingChar();
	if (c == 0)
	{
		UngetChar();
		return nullptr;
	}

	auto Token = std::make_shared<CppToken>();
	Token->StartPos = PrevPos;
	Token->StartLine = PrevLine;

	TCHAR p = PeekChar();
	if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'))
	{
		int32 Length = 0;
		do
		{
			Token->Identifier[Length++] = c;
			if(Length > CppToken::NAME_SIZE)
			{
				RE_ASSERT_MSG(false, "Identifer length exceeds maximum of {0}", (int32)CppToken::NAME_SIZE)
				Length = ((int32)CppToken::NAME_SIZE) - 1;
				break;
			}
			c = GetChar();
		} while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_'));
		UngetChar();
		Token->Identifier[Length] = 0;
		// Assume this is an identifier unless we find otherwise.
		Token->TokenType = CppTokenType::Identifier;

		if(!bNoConsts)
		{
			if(Token->Matches("true"))
			{
				Token->SetConstBool(true);
				return Token;
			}
			else if(Token->Matches("false"))
			{
				Token->SetConstBool(false);
				return Token;
			}
		}
		return Token;
	}
	// if const values are allowed, determine whether the non-identifier token represents a const
	else if (!bNoConsts && ((c >= '0' && c <= '9') || ((c == '+' || c == '-') && (p >= '0' && p <= '9'))))
	{
		// Integer or floating point constant.
		bool  bIsFloat = 0;
		int32 Length = 0;
		bool  bIsHex = 0;

		do
		{
			if (c == '.')
			{
				bIsFloat = true;
			}
			if (c == 'X' || c == 'x')
			{
				bIsHex = true;
			}

			Token->Identifier[Length++] = c;
			if (Length >= CppToken::NAME_SIZE)
			{
				RE_ASSERT_MSG(false, "Number length exceeds maximum of {} ", (int32)CppToken::NAME_SIZE)
				Length = ((int32)CppToken::NAME_SIZE) - 1;
				break;
			}
			
			c = StringEx::ToUpper(GetChar());
		} while ((c >= '0' && c <= '9') || (!bIsFloat && c == '.') || (!bIsHex && c == 'X') || (bIsHex && c >= 'A' && c <= 'F'));

		Token->Identifier[Length] = 0;
		if (!bIsFloat || c != 'F')
		{
			UngetChar();
		}

		if (bIsFloat)
		{
			Token->SetConstFloat(StringEx::Atof(Token->Identifier));
		}
		else if (bIsHex)
		{
			TCHAR* End = Token->Identifier + StringEx::StrLen(Token->Identifier);
			Token->SetConstInt64(StringEx::Strtoi64(Token->Identifier, &End, 0));
		}
		else
		{
			Token->SetConstInt64(StringEx::Atoi64(Token->Identifier));
		}
		return Token;
	}
	else if (c == '\'')
	{
		TCHAR ActualCharLiteral = GetChar(/*bLiteral=*/ true);

		if (ActualCharLiteral == '\\')
		{
			ActualCharLiteral = GetChar(/*bLiteral=*/ true);
			switch (ActualCharLiteral)
			{
			case TCHAR('t'):
				ActualCharLiteral = '\t';
				break;
			case TCHAR('n'):
				ActualCharLiteral = '\n';
				break;
			case TCHAR('r'):
				ActualCharLiteral = '\r';
				break;
			}
		}

		c = GetChar(/*bLiteral=*/ true);
		if (c != '\'')
		{
			RE_ASSERT_MSG(false, "Unterminated character constant");
			UngetChar();
		}

		Token->SetConstChar(ActualCharLiteral);
		return Token;
	}
	else if (c == '"')
	{
		// String constant.
		TCHAR Temp[CppToken::MAX_STRING_CONST_SIZE];
		int32 Length = 0;
		c = GetChar(/*bLiteral=*/ true);
		while ((c != '"') && !IsEOL(c))
		{
			if (c == '\\')
			{
				c = GetChar(/*bLiteral=*/ true);
				if (IsEOL(c))
				{
					break;
				}
				else if (c == 'n')
				{
					// Newline escape sequence.
					c = '\n';
				}
			}
			Temp[Length++] = c;
			if (Length >= CppToken::MAX_STRING_CONST_SIZE)
			{
				RE_ASSERT_MSG(false, "String constant exceeds maximum of {} characters", (int32)CppToken::MAX_STRING_CONST_SIZE)
				c = '\"';
				Length = ((int32)CppToken::MAX_STRING_CONST_SIZE) - 1;
				break;
			}
			c = GetChar(/*bLiteral=*/ true);
		}
		Temp[Length] = 0;

		if (c != '"')
		{
			RE_ASSERT_MSG(false, "Unterminated string constant: {}", Temp)
			UngetChar();
		}

		Token->SetConstString(Temp);
		return Token;
	}
	else
	{
		// Symbol.
		int32 Length = 0;
		Token->Identifier[Length++] = c;

		// Handle special 2-character symbols.
		#define PAIR(cc,dd) ((c==cc)&&(d==dd)) /* Comparison macro for convenience */
		TCHAR d = GetChar();
		if
			(PAIR('<', '<')
				|| (PAIR('>', '>'))
				|| PAIR('!', '=')
				|| PAIR('<', '=')
				|| PAIR('>', '=')
				|| PAIR('+', '+')
				|| PAIR('-', '-')
				|| PAIR('+', '=')
				|| PAIR('-', '=')
				|| PAIR('*', '=')
				|| PAIR('/', '=')
				|| PAIR('&', '&')
				|| PAIR('|', '|')
				|| PAIR('^', '^')
				|| PAIR('=', '=')
				|| PAIR('*', '*')
				|| PAIR('~', '=')
				|| PAIR(':', ':')
				)
		{
			Token->Identifier[Length++] = d;
			if (c == '>' && d == '>')
			{
				if (GetChar() == '>')
				{
					Token->Identifier[Length++] = '>';
				}
				else
				{
					UngetChar();
				}
			}
		}
		else
		{
			UngetChar();
		}
		#undef PAIR

		Token->Identifier[Length] = 0;
		Token->TokenType = CppTokenType::Symbol;

		return Token;
	}
}

void BaseParser::UngetToken(const SharedPtr<CppToken>& Token)
{
	InputPos = Token->StartPos;
	InputLine = Token->StartLine;
}

SharedPtr<CppToken> BaseParser::GetIdentifier(bool bNoConsts)
{
	auto Token = GetToken(bNoConsts);
	if (!Token)
	{
		return nullptr;
	}

	if (Token->TokenType == CppTokenType::Identifier)
	{
		return Token;
	}

	UngetToken(Token);
	return nullptr;
}

SharedPtr<CppToken> BaseParser::GetSymbol()
{
	auto Token = GetToken();
	if (!Token)
	{
		return nullptr;
	}

	if (Token->TokenType == CppTokenType::Symbol)
	{
		return Token;
	}

	UngetToken(Token);
	return nullptr;
}

bool BaseParser::GetConstInt(int32& Result, const TCHAR* Tag)
{
	auto Token = GetToken();
	if(Token)
	{
		if(Token->GetConstInt(Result))
		{
			return true;
		}
		else
		{
			UngetToken(Token);
		}
	}

	if(Tag != nullptr)
	{
		RE_ASSERT_MSG(false, "%s : Missing constant integer", Tag)
	}

	return false;
}

bool BaseParser::GetConstInt64(int64& Result, const TCHAR* Tag)
{
	auto Token = GetToken();
	if (Token)
	{
		if (Token->GetConstInt64(Result))
		{
			return true;
		}
		else
		{
			UngetToken(Token);
		}
	}

	if (Tag != nullptr)
	{
		RE_ASSERT_MSG(false, "%s : Missing constant integer", Tag)
	}

	return false;
}

bool BaseParser::MatchIdentifier(const TCHAR* Match)
{
	auto Token = GetToken();
	if(Token != nullptr)
	{
		if(Token->GetTokenType() == CppTokenType::Identifier &&
			Token->Matches(Match))
		{
			return true;
		}
		else
		{
			UngetToken(Token);
		}
	}
	return false;
}

bool BaseParser::MatchConstInt(const TCHAR* Match)
{
	auto Token = GetToken();
	if(Token)
	{
		if(Token->GetTokenType() == CppTokenType::Const 
			&& (Token->GetConstType() == CppTokenConstType::Int || Token->GetConstType() == CppTokenConstType::Int64)
			&& Token->GetTokenName() == Match)
		{
			return true;
		}
		else
		{
			UngetToken(Token);
		}
	}
	
	return false;
}

bool BaseParser::MatchAnyConstInt()
{
	auto Token = GetToken();
	if (Token)
	{
		if (Token->GetTokenType() == CppTokenType::Const
			&& (Token->GetConstType() == CppTokenConstType::Int 
				|| Token->GetConstType() == CppTokenConstType::Int64))
		{
			return true;
		}
		else
		{
			UngetToken(Token);
		}
	}

	return false;
}

bool BaseParser::PeekIdentifier(const TCHAR* Match)
{
	auto Token = GetToken(true);
	if(!Token)
	{
		return false;
	}
	UngetToken(Token);
	return Token->GetTokenType() == CppTokenType::Identifier
		&& Token->GetTokenName() == Match;
}

bool BaseParser::MatchSymbol(const TCHAR Match)
{
	auto Token = GetToken(true);
	if(Token)
	{
		if(Token->GetTokenType() == CppTokenType::Symbol 
			&& Token->GetRawTokenName()[0] == Match 
			&& Token->GetRawTokenName()[1] == 0)
		{
			return true;
		}else
		{
			UngetToken(Token);
		}
	}
	return false;
}

bool BaseParser::MatchSymbol(const TCHAR* Match)
{
	auto Token = GetToken(true);
	if (Token)
	{
		if (Token->GetTokenType() == CppTokenType::Symbol
			&& Token->GetTokenName() == Match)
		{
			return true;
		}
		else
		{
			UngetToken(Token);
		}
	}
	return false;
}

bool BaseParser::MatchToken(Function<bool(const CppToken&)> Condition)
{
	auto Token = GetToken(true);
	if (Token)
	{
		if (Condition(*Token))
		{
			return true;
		}
		else
		{
			UngetToken(Token);
		}
	}
	return false;
}

bool BaseParser::MatchSemi()
{
	if (MatchSymbol(';'))
	{
		return true;
	}
	return false;
}

void BaseParser::RequireSemi()
{
	if(!MatchSymbol(';'))
	{
		auto Token = GetToken();
		if(Token)
		{
			RE_ASSERT_MSG(false, "Missing ';' before %s", Token->GetRawTokenName())
		}
		else
		{
			RE_ASSERT_MSG(false, "Missing ';'")
		}
	}
}

AString BaseParser::GetLocation() const
{
	return fmt::format("{0}:{1}", InputLine, InputPos);
}

bool BaseParser::PeekSymbol(const TCHAR Match)
{
	auto Token = GetToken(true);
	if(!Token)
	{
		return false;
	}
	UngetToken(Token);
	return Token->GetTokenType() == CppTokenType::Symbol
		&& Token->GetRawTokenName()[0] == Match
		&& Token->GetRawTokenName()[1] == 0;
}

void BaseParser::RequireIdentifier(const TCHAR* Match, const TCHAR* Tag)
{
	RE_ASSERT_MSG(MatchIdentifier(Match), "Missing '%s' in %s", Match, Tag)
}

void BaseParser::RequireSymbol(const TCHAR Match, const TCHAR* Tag)
{
	RE_ASSERT_MSG(MatchSymbol(Match), "Missing %c in %s", Match, Tag)
}

void BaseParser::RequireSymbol(const TCHAR Match, Function<AString()> TagGetter)
{
	RE_ASSERT_MSG(MatchSymbol(Match), "Missing %c in %s", Match, TagGetter().c_str())
}

void BaseParser::RequireConstInt(const TCHAR* Match, const TCHAR* Tag)
{
	RE_ASSERT_MSG(MatchConstInt(Match), "Missing integer '%s' in %s", Match, Tag);
}

void BaseParser::RequireAnyConstInt(const TCHAR* Tag)
{
	RE_ASSERT_MSG(MatchAnyConstInt(), "Missing integer in %s'", Tag)
}
