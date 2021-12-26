#pragma once

#include "CommonHeader.h"
#include "CppCodeParser_API.h"

class CppToken;

class CppCodeParser_API BaseParser
{
	DEFINE_CLASS(BaseParser)
public:

	void InitParserSource(const char* SourceBuffer);

	// Basic Operations
	
	TCHAR GetChar(bool Literal = false);
	TCHAR PeekChar();
	TCHAR GetLeadingChar();
	void UngetChar();

	/**
	 * Tests if a character is an end-of-line character.
	 *
	 * @param	c	The character to test.
	 *
	 * @return	true if c is an end-of-line character, false otherwise.
	 */
	static bool IsEOL(TCHAR c);

	/**
	 * Tests if a character is a whitespace character.
	 *
	 * @param	c	The character to test.
	 *
	 * @return	true if c is an whitespace character, false otherwise.
	 */
	static bool IsWhitespace(TCHAR c);

	/** Clears out the stored comment. */
	void ClearComment();

public:

	/**
	 * \brief 
	 * \param bNoConsts ignore Const
	 * \return 
	 */
	SharedPtr<CppToken> GetToken(bool bNoConsts = false);

	void UngetToken(const SharedPtr<CppToken>& Token);

	SharedPtr<CppToken>  GetIdentifier(bool bNoConsts = false);
	SharedPtr<CppToken> GetSymbol();

	// TODO
	// bool GetConstInt(int32& Result, const TCHAR* Tag = NULL);
	// bool GetConstInt64(int64& Result, const TCHAR* Tag = NULL);

	// Matching predefined text.
	// bool MatchIdentifier(const TCHAR* Match);
	// bool MatchConstInt(const TCHAR* Match);
	// bool MatchAnyConstInt();
	// bool PeekIdentifier(const TCHAR* Match);
	// bool MatchSymbol(const TCHAR Match);
	// bool MatchSymbol(const TCHAR* Match);
	// void MatchSemi();
	// bool PeekSymbol(const TCHAR Match);

	// Requiring predefined text.
	// void RequireIdentifier(const TCHAR* Matc, const TCHAR* Tag);
	// void RequireSymbol(const TCHAR Match, const TCHAR* Tag);
	// void RequireSymbol(const TCHAR Match, Function<AString()> TagGetter);
	// void RequireConstInt(const TCHAR* Match, const TCHAR* Tag);
	// void RequireAnyConstInt(const TCHAR* Tag);


	bool CompileDeclaration(SharedPtr<CppToken> Token);

protected:

	// Input text
	const TCHAR* Input;
	// Length of input text
	int32 InputLen;
	// Current position in text
	int32 InputPos;
	// Current line in text
	int32 InputLine;
	// last GetChar line
	int32 PrevPos;
	// last GetChar pos
	int32 PrevLine;
	// Previous comment parsed by GetChar() call.
	AString PrevComment;
	// Number of statements parsed.
	int32 StatementsParsed;
	// Total number of lines parsed.
	int32 LinesParsed;

};
