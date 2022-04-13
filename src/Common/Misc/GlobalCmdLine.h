#pragma once
#include "Singleton.h"
#include "cmdline.h"
#include "ResetCore_CommonLib_API.h"

class ResetCore_CommonLib_API GlobalCmdLine
{
	DEFINE_SINGLETON(GlobalCmdLine)
public:

	void Init(int argc, char* argv[]);

	template<typename T>
	T Get(const std::string& Name)
	{
		return Parser.get<T>();
	}

	int GetArgc() const
	{
		return Argc;
	}

	char** GetArgv() const
	{
		return Argv;
	}


private:
	int Argc;
	char** Argv;
	cmdline::parser Parser;
};