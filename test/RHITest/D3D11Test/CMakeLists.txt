
set(targetName "Test_D3D11RHI")
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE EXE
        LIB D3D11RHI
            ResetCore_Framework
            ResetCore_CommonLib
        )


ReMake_StartUse()
UseWinMain(${targetName})
ReMake_EndUse()