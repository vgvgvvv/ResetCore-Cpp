#pragma once

#include "Common.h"
#include "ResetCore_CommonLib_API.h"

namespace CommonLib
{
    // Forward declarations
    ResetCore_CommonLib_API void* LoadModuleLibrary(const T_CHAR*);
    ResetCore_CommonLib_API void* GetModuleExport(void*, const char*);
}
