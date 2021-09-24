#pragma once
#include "Singleton.h"
#include "Class/ClassInfo.h"
#include "VulkanRHI_API.h"

#include <windows.h>

class VulkanInstance;
class VulkanDebugLayer;
class VulkanSurface;

class VulkanRHI_API VulkanRHI
{
	DEFINE_SINGLETON(VulkanRHI)
public:

	void Init(HINSTANCE windowInstance, HWND window);
	void Uninit();

private:
	VulkanInstance* instance;
	VulkanDebugLayer* debugLayer;
	VulkanSurface* surface;
};
