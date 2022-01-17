#include "EnumScope.h"
#include "Json/JsonSerialization.h"

DEFINE_DERIVED_CLASS_IMP(EnumScope, BaseScope)
BEGIN_TO_JSON(EnumScope)
BASE_TO_JSON(BaseScope)
TO_JSON_ARG_WITH_GETTER(FieldInfos)
END_TO_JSON()
DEFINE_TO_JSON_MEMBER_IMP(EnumScope)