

set(targetName "ParserTest")
ReMake_AddTarget(
    TARGET_NAME ${targetName}
    MODE EXE
    LIB CppCodeParser 
        ResetCore_CommonLib)