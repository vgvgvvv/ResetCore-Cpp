#include "GlobalCmdLine.h"

void GlobalCmdLine::Init(int argc, char* argv[])
{
	Argc = argc;
	Argv = argv;
	Parser.parse(argc, argv);
}
