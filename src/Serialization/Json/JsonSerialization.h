#pragma once

#include "CommonHeader.h"
#include "nlohmann/json.hpp"
#include "ResetCore_Serialization_API.h"

template<typename T>
nlohmann::json ToJson(const T& Obj)
{
	static_assert(false, "Not Support Current Type!!");
}

template<typename T>
nlohmann::json ToJson(const Vector<T>& Obj)
{
	nlohmann::json Arr;
}

class ResetCore_Serialization_API JsonSerialization
{
	template<typename T>	
	static nlohmann::json SerializeAny(const T& Obj)
	{
		return ToJson<T>(Obj);
	}
};