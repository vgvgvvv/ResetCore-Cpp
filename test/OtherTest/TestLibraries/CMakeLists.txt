
set(targetName "Test_Libraries")
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE EXE
        LIB Luau.VM
            Luau.Compiler
            sol2)

ReMake_StartUse()
UseLuau(${targetName})
UseSol2(${targetName})
ReMake_EndUse()