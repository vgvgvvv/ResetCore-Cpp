#pragma once 
#include "Application/Layer.h"
#if PLATFORM_WINDOWS
#include <windows.h>
#endif

class VulkanRHILayer : public Layer
{
public:
#if PLATFORM_WINDOWS
	VulkanRHILayer(HINSTANCE appInstance, HWND mhMainWnd)
		: appInstance(appInstance)
		, mhMainWnd(mhMainWnd)
	{
	}
#endif
	void OnInit() override;
	void OnShutDown() override;

private:
	HINSTANCE appInstance;
	HWND      mhMainWnd = nullptr;

};
