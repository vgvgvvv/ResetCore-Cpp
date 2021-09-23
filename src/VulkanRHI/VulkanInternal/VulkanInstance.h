#pragma once
#include "vulkan/vulkan.h"

class VulkanInstance
{
public:
	void Init();
	~VulkanInstance();
private:

	VkInstance instance = VK_NULL_HANDLE;
};