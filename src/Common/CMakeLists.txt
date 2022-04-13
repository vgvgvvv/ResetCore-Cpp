
ReMake_ShowIncludeFileName()

set(TargetName ResetCore_CommonLib)
ReMake_AddTarget(
	TARGET_NAME ${TargetName}
	MODE SHARED
	LIB tf::default_settings
	LIB_INTERFACE ResetCore_Template
)

ReMake_StartUse()
UseSpdLog(${TargetName})
UseFmt(${TargetName})
UseTinyDir(${TargetName})
UseIniFile(${TargetName})
UseFileDialog(${TargetName})
UseTaskflow(${TargetName})
UseCmdLine(${TargetName})
ReMake_EndUse()