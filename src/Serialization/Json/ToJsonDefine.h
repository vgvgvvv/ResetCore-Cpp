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
static_assert(std::is_base_of_v<BaseClassName, std::decay_t<decltype(*this)>>, "Must Derived From " #BaseClassName); \
Result = ToJsonWrapper<BaseClassName>::ToJson(*this);


#define TO_JSON_ARG(ArgName) \
Result[#ArgName] = ToJsonWrapper<decltype(ArgName)>::ToJson(ArgName);

#define TO_JSON_ARG_WITH_GETTER(ArgName) \
Result[#ArgName] = ToJsonWrapper<decltype(get_##ArgName())>::ToJson(get_##ArgName());

#define END_TO_JSON() \
		return Result; \
	} \
};

#define DEFINE_TO_JSON_MEMBER() \
public: \
nlohmann::json ToJson() const; \
private:

#define BEGIN_TO_JSON_MEMBER_IMP(ClassName) \
nlohmann::json ClassName::ToJson() const \
{ \
	nlohmann::json Result;

#define END_TO_JSON_MEMBER_IMP() \
	return Result; \
};