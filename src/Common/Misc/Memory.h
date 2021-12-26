#pragma once

#include <memory>
#include "Platform/Platform.h"
#include "ResetCore_CommonLib_API.h"

class ResetCore_CommonLib_API MemoryLibrary
{

public:
	static void* Memmove(void* Dest, const void* Src, SIZET Count)
	{
		return memmove(Dest, Src, Count);
	}

	static int32 Memcmp(const void* Buf1, const void* Buf2, SIZET Count)
	{
		return memcmp(Buf1, Buf2, Count);
	}

	static void* Memset(void* Dest, uint8 Char, SIZET Count)
	{
		return memset(Dest, Char, Count);
	}

	static void* Memzero(void* Dest, SIZET Count)
	{
		return memset(Dest, 0, Count);
	}

	template< class T >
	static void Memzero(T& Src)
	{
		static_assert(!std::is_pointer_v<T>, "For pointers use the two parameters function");
		Memzero(&Src, sizeof(T));
	}

	static void* Memcpy(void* Dest, const void* Src, SIZET Count)
	{
		return memcpy(Dest, Src, Count);
	}

	/** Memcpy optimized for big blocks. */
	static void* BigBlockMemcpy(void* Dest, const void* Src, SIZET Count)
	{
		return memcpy(Dest, Src, Count);
	}

	/** On some platforms memcpy optimized for big blocks that avoid L2 cache pollution are available */
	static void* StreamingMemcpy(void* Dest, const void* Src, SIZET Count)
	{
		return memcpy(Dest, Src, Count);
	}
};