
set(targetName "Test_Libraries")
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE EXE
        LIB Luau.VM
            Luau.Compiler)

ReMake_StartUse()
UseLuau(${targetName})
ReMake_EndUse()