
set(targetName "ReflectionCodeGenerator")
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE SHARED
        LIB ResetCore_CommonLib
            ResetCore_Serialization
            CppCodeParser)

ReMake_StartUse()
UseJson(${targetName})
ReMake_EndUse()