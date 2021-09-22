set(targetName D3D12RHI)
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE SHARED
        ResetCore_CommonLib
)

ReMake_StartUse()
UseDirectX12(${targetName})
ReMake_EndUse()