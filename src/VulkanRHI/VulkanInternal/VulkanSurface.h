#pragma once 

#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"

class VulkanSurface
{
public:
	void Init(VkInstance instance, HINSTANCE windowInstance, HWND window);
	void Uninit(VkInstance instance);

	DEFINE_GETTER(VkSurfaceKHR, surface);
	
private:
	VkSurfaceKHR surface = VK_NULL_HANDLE;
};