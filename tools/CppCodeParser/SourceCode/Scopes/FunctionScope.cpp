#include "FunctionScope.h"
#include "Json/JsonSerialization.h"

DEFINE_DERIVED_CLASS_IMP(FunctionScope, BaseScope)
BEGIN_TO_JSON(FunctionScope)
BASE_TO_JSON(BaseScope)
END_TO_JSON()
DEFINE_TO_JSON_MEMBER_IMP(FunctionScope)