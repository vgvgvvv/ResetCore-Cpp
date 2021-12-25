#include "Token.h"


DEFINE_CLASS_IMP(BaseToken)
DEFINE_DERIVED_CLASS_IMP(IdentifierToken, BaseToken)
DEFINE_DERIVED_CLASS_IMP(SymbolToken, BaseToken)