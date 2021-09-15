
ReMake_ShowIncludeFileName()

set(TargetName ResetCore_CommonLib)
ReMake_AddTarget(
	TARGET_NAME ${TargetName}
	MODE SHARED
	LIB_INTERFACE ResetCore_Template
)

ReMake_StartUse()
UseSpdLog(${TargetName})
UseFmt(${TargetName})
UseTinyDir(${TargetName})
UseIniFile(${TargetName})
UseFileDialog(${TargetName})
ReMake_EndUse()