
set(targetName "CppCodeParser")
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE SHARED
        LIB ResetCore_CommonLib)

ReMake_StartUse()
UseJson(${targetName})
ReMake_EndUse()