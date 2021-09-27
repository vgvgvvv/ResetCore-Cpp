#pragma once
#include "ResetCore_CommonLib_API.h"

namespace Common
{
#if PLATFORM_WINDOWS
	namespace Windows
	{
		ResetCore_CommonLib_API void ShowConsole(const char* title);
	}
#endif
};