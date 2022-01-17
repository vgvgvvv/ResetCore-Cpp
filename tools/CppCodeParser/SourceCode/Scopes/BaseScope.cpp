#include "BaseScope.h"
#include "Json/JsonSerialization.h"

DEFINE_CLASS_IMP(BaseScope)

BEGIN_TO_JSON_MEMBER_IMP(BaseScope)
Result["Class"] = GetClass()->Name();
Result["Name"] = GetName();
END_TO_JSON_MEMBER_IMP()