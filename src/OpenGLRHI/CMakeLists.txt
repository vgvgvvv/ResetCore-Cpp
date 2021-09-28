set(targetName OpenGLRHI)
ReMake_AddTarget(
        TARGET_NAME ${targetName}
        MODE SHARED
        LIB ResetCore_CommonLib
)

ReMake_StartUse()
Gml_UseMsExtension(ON)
UseGml(${targetName})
UseGlfw(${targetName})
UseGlew(${targetName})
UseOpengl(${targetName})
ReMake_EndUse()