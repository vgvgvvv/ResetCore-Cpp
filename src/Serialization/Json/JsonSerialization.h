#pragma once

#include "CommonHeader.h"
#include "nlohmann/json.hpp"
#include "String/StringSerialization.h"
#include "ResetCore_Serialization_API.h"

namespace __TO_JSON_DETAIL
{
    // SFINAE test
    template <typename T>
    class HasToJson
    {
        typedef char one;
        struct two { char x[2]; };

        template <typename C>
        static one test(decltype(&C::ToJson));
        template <typename C>
        static two test(...);

    public:
        enum { Value = sizeof(test<T>(0)) == sizeof(char) };
    };
}

template<typename T, typename = void>
struct ToJsonWrapper
{
    static nlohmann::json ToJson(const T& Obj)
    {
        return Obj;
    }
};

template<typename T>
struct ToJsonWrapper<T, typename std::enable_if_t<__TO_JSON_DETAIL::HasToJson<T>::Value>>
{
    static nlohmann::json ToJson(const T& Obj)
    {
        return Obj.ToJson();
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
        T& Out = *Obj;
        return ToJsonWrapper<T>::ToJson(Out);
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

