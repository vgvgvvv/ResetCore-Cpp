#pragma once
#include "nlohmann/json.hpp"


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

#define DEFINE_TO_JSON_MEMBER() \
public: \
nlohmann::json ToJson() const; \
private:

#define DEFINE_TO_JSON_MEMBER_IMP(ClassName) \
nlohmann::json ClassName::ToJson() const \
{ \
    return ToJsonWrapper<ClassName>::ToJson(*this); \
}
