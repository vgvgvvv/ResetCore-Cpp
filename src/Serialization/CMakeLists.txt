

ReMake_ShowIncludeFileName()

set(TargetName ResetCore_Serialization)
ReMake_AddTarget(
	TARGET_NAME ${TargetName}
	MODE SHARED
	LIB ResetCore_CommonLib
)


ReMake_StartUse()
UseJson(${TargetName})
ReMake_EndUse()