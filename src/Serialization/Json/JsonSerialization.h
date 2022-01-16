#pragma once

#include "CommonHeader.h"
#include "nlohmann/json.hpp"
#include "String/StringSerialization.h"
#include "ResetCore_Serialization_API.h"

template<typename T>
struct ToJsonWrapper
{
    static nlohmann::json ToJson(const T& Obj)
    {
        return Obj;
    }
};

template<typename T>
struct ToJsonWrapper<const T&>
{
    static nlohmann::json ToJson(const T& Obj)
    {
        return ToJsonWrapper<T>::ToJson(Obj);
    }
};

template<typename T>
struct ToJsonWrapper<std::decay<T>>
{
    static nlohmann::json ToJson(const std::decay<T>& Obj)
    {
        return Obj;
    }
};

template<typename T>
struct ToJsonWrapper<std::vector<T>>
{
    static nlohmann::json ToJson(const std::vector<T>& Obj)
    {
        nlohmann::json Arr = nlohmann::json::array();
        for (const auto& Item : Obj) {
            Arr.push_back(ToJsonWrapper<T>::ToJson(Item));
        }
        return Arr;
    }
};


template<typename K, typename V>
struct ToJsonWrapper<Map<K, V>>
{
    static nlohmann::json ToJson(const Map<K, V>& Obj)
    {
        nlohmann::json Result;
        for (const auto& Item : Obj)
        {
            Result[ToString(Item.first)] = ToJsonWrapper<V>::ToJson(Item.second);
        }
        return Result;
    }
};


template<typename T>
struct ToJsonWrapper<std::shared_ptr<T>>
{
    static nlohmann::json ToJson(const std::shared_ptr<T>& Obj)
    {
        return ToJsonWrapper<T>::ToJson(*Obj);
    }
};

template<typename T>
nlohmann::json ToJson(const T& Obj)
{
    return ToJsonWrapper<T>::ToJson(Obj);
}

class ResetCore_Serialization_API JsonSerialization
{
	template<typename T>	
	static nlohmann::json SerializeAny(const T& Obj)
	{
		return ToJson<T>(Obj);
	}
};

#define BEGIN_TO_JSON(ClassName) \
template<> \
struct ToJsonWrapper<ClassName> \
{ \
    static nlohmann::json ToJson(const ClassName& Obj) \
    { \
        nlohmann::json Result;

#define BASE_TO_JSON(BaseClassName)\
static_assert(std::is_base_of_v<BaseClassName, std::decay_t<decltype(Obj)>>, "Must Derived From " #BaseClassName); \
Result = ToJsonWrapper<BaseClassName>::ToJson(Obj);


#define TO_JSON_ARG(ArgName) \
Result[#ArgName] = ToJsonWrapper<decltype(Obj.ArgName)>::ToJson(Obj.ArgName);

#define TO_JSON_ARG_WITH_GETTER(ArgName) \
Result[#ArgName] = ToJsonWrapper<decltype(Obj.get_##ArgName())>::ToJson(Obj.get_##ArgName());

#define END_TO_JSON() \
		return Result; \
	} \
};