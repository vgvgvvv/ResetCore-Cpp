

set(targetName "ReHeaderTool")
ReMake_AddTarget(
    TARGET_NAME ${targetName}
    MODE EXE
    LIB CppCodeParser 
        ResetCore_CommonLib)


add_custom_command(
    TARGET ${targetName}
    PRE_BUILD
    COMMAND echo hello prebuild)

add_custom_command(
    TARGET ${targetName} 
    PRE_LINK
    COMMAND echo hello prelink)

add_custom_command(
    TARGET ${targetName}
    POST_BUILD
    COMMAND echo hello postbuild)