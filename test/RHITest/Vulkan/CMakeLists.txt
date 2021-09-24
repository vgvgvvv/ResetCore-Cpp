
set(targetName "Test_VulkanRHI")
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE EXE
        LIB VulkanRHI
            ResetCore_Framework
            ResetCore_CommonLib
        )


ReMake_StartUse()
UseWinMain(${targetName})
ReMake_EndUse()