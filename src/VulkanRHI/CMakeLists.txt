set(targetName VulkanRHI)
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE SHARED
        LIB ResetCore_CommonLib
        DEFINE VK_VERSION_1_0 GLFW_INCLUDE_VULKAN
)

ReMake_StartUse()
Gml_UseMsExtension(ON)
UseGml(${targetName})
UseGlfw(${targetName})
UseVulkan(${targetName})
UseShaderc(${targetName})
ReMake_EndUse()