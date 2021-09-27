#pragma once
#include "Singleton.h"
#include "Class/ClassInfo.h"
#include "VulkanSetting.h"
#include "VulkanRHI_API.h"

class VulkanInstance;
class VulkanSurface;
class VulkanDevice;

struct WindowInfo
{
	int width;
	int height;
#if PLATFORM_WINDOWS
	HINSTANCE windowInstance;
	HWND window;
#endif
};

class VulkanRHI_API VulkanRHI
{
	DEFINE_SINGLETON(VulkanRHI)
public:

	void Init(WindowInfo windowInfo);
	void Uninit();

	DEFINE_GETTER(WindowInfo, windowInfo);
	
private:
	VulkanInstance* instance;
	VulkanDevice* device;

	WindowInfo windowInfo;
};
