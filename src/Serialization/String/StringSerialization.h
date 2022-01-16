#pragma once

#include "CommonHeader.h"
#include "ResetCore_Serialization_API.h"

template<typename T>
AString ToString(const T& Obj)
{
	static_assert(false, "Not Support Current Type!!");
}

template<>
AString ToString<AString>(const AString& Obj)
{
    return Obj;
}

class ResetCore_Serialization_API StringSerialization
{
	template<typename T>
	static AString SerializeAny(const T& Obj)
	{
		return ToString<T>(Obj);
	}
};