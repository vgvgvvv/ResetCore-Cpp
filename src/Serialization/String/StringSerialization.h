#pragma once

#include "CommonHeader.h"
#include "ResetCore_Serialization_API.h"

template<typename T>
struct ToStringWrapper
{
	static AString ToString(const T& Obj)
	{
		static_assert(false, "Not Support Current Type!!");
		return "";
	}
};


template<>
struct ToStringWrapper<AString>
{
	static AString ToString(const AString& Obj)
	{
		return Obj;
	}
};

template<typename T>
AString ToString(const T& Obj)
{
	return ToStringWrapper<T>::ToString(Obj);
}

class ResetCore_Serialization_API StringSerialization
{
	template<typename T>
	static AString SerializeAny(const T& Obj)
	{
		return ToString<T>(Obj);
	}
};