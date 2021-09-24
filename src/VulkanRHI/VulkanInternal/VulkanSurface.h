#pragma once 

#include "vulkan/vulkan.h"

class VulkanSurface
{
public:
	void Init(VkInstance instance, HINSTANCE windowInstance, HWND window);
	void Uninit(VkInstance instance);

private:
	VkSurfaceKHR surface = VK_NULL_HANDLE;
};