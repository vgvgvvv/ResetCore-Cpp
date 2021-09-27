#include "WindowsMisc.h"
#include <iostream>
#include<windows.h>

namespace Common
{
#if PLATFORM_WINDOWS
	namespace Windows
	{
		 void ShowConsole(const char* title)
		{
			AllocConsole();  //create console
			SetConsoleTitle(title); //set console title   
			FILE* tempFile = nullptr;
			freopen_s(&tempFile, "conin$", "r+t", stdin); //reopen the stdin, we can use std::cout.
			freopen_s(&tempFile, "conout$", "w+t", stdout);
		}
	}
#endif	
}
