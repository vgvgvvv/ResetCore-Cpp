#pragma once
#include "Singleton.h"
#include "Class/ClassInfo.h"
#include "VulkanRHI_API.h"
#include "VulkanInternal/VulkanInstance.h"
#include "VulkanInternal/VulkanDebugLayer.h"
#include "VulkanInternal/VulkanSurface.h"

class VulkanRHI_API VulkanRHI
{
	DEFINE_SINGLETON(VulkanRHI)
public:

	void Init(HINSTANCE windowInstance, HWND window);
	void Uninit();

	DEFINE_GETTER(VulkanInstance, instance);
	DEFINE_GETTER(VulkanDebugLayer, debugLayer);
	DEFINE_GETTER(VulkanSurface, surface);

	
private:
	VulkanInstance instance;
	VulkanDebugLayer debugLayer;
	VulkanSurface surface;
};
