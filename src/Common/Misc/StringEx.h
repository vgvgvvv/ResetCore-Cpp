#pragma once
#include <string>
#include <vector>
#include <cstring>

#include "ResetCore_CommonLib_API.h"
#include "Platform/Platform.h"

class ResetCore_CommonLib_API StringEx
{
public:
	static void ReplaceAll(std::string& str, const std::string& from, const std::string& to);

	static std::vector<std::string> Split(const std::string& str, const std::string& split);

	static bool Strcpy(ANSICHAR* Dest, SIZET DestCount, const ANSICHAR* Src)
	{
		return (ANSICHAR*)strcpy(Dest, Src);
	}

	static void Strncpy(ANSICHAR* Dest, const ANSICHAR* Src, SIZET MaxLen)
	{
		strncpy(Dest, Src, MaxLen);
		Dest[MaxLen - 1] = 0;
	}

	static ANSICHAR* Strupr(ANSICHAR* Dest, SIZET DestCount)
	{
		return (ANSICHAR*)_strupr(Dest);
	}

	static bool Strcmp(const char* str1, const char* str2)
	{
		return strcmp(str1, str2);
	}

	static int32 StrLen(const char* str)
	{
		return strlen(str);
	}

	static int32 Strnlen(const ANSICHAR* String, SIZET StringSize)
	{
		return strnlen(String, StringSize);
	}

	static const ANSICHAR* Strstr(const ANSICHAR* String, const ANSICHAR* Find)
	{
		return strstr(String, Find);
	}

	static const ANSICHAR* Strchr(const ANSICHAR* String, ANSICHAR C)
	{
		return strchr(String, C);
	}

	static const ANSICHAR* Strrchr(const ANSICHAR* String, ANSICHAR C)
	{
		return strrchr(String, C);
	}

	static char ToUpper(char InChar)
	{
		return toupper(InChar);
	}

	static char ToLower(char InChar)
	{
		return tolower(InChar);
	}

	static int32 Atoi(const ANSICHAR* String)
	{
		return atoi(String);
	}

	static int64 Atoi64(const ANSICHAR* String)
	{
		return _strtoi64(String, NULL, 10);
	}

	static float Atof(const ANSICHAR* String)
	{
		return (float)atof(String);
	}

	static double Atod(const ANSICHAR* String)
	{
		return atof(String);
	}

	static int32 Strtoi(const ANSICHAR* Start, ANSICHAR** End, int32 Base)
	{
		return strtol(Start, End, Base);
	}

	static int64 Strtoi64(const ANSICHAR* Start, ANSICHAR** End, int32 Base)
	{
		return _strtoi64(Start, End, Base);
	}

	static uint64 Strtoui64(const ANSICHAR* Start, ANSICHAR** End, int32 Base)
	{
		return _strtoui64(Start, End, Base);
	}

	static ANSICHAR* Strtok(ANSICHAR* StrToken, const ANSICHAR* Delim, ANSICHAR** Context)
	{
		return strtok_s(StrToken, Delim, Context);
	}

};
