#include "FunctionScope.h"
#include "Json/JsonSerialization.h"

DEFINE_DERIVED_CLASS_IMP(FunctionScope, BaseScope)
BEGIN_TO_JSON_MEMBER_IMP(FunctionScope)
BASE_TO_JSON(BaseScope)
END_TO_JSON_MEMBER_IMP()
