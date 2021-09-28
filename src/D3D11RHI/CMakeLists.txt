set(targetName D3D11RHI)
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE SHARED
        LIB ResetCore_CommonLib
)

ReMake_StartUse()
UseDirectX11(${targetName})
ReMake_EndUse()