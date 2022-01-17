#include "BaseScope.h"
#include "Json/JsonSerialization.h"

DEFINE_CLASS_IMP(BaseScope)

BEGIN_TO_JSON(BaseScope)
Result["Class"] = Obj.GetClass()->Name();
Result["Name"] = Obj.GetName();
END_TO_JSON()

DEFINE_TO_JSON_MEMBER_IMP(BaseScope)

