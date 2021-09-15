
ReMake_ShowIncludeFileName()

set(targeName ResetCore_Framework)
ReMake_AddTarget(
	TARGET_NAME ${targeName}
	MODE SHARED
	LIB ResetCore_Template
		ResetCore_Common
)