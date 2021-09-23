#pragma once
#include <vector>

#include "vulkan/vulkan.h"

class VulkanInstance
{
public:
	void Init();
	~VulkanInstance();
private:
	std::vector<const char*> instanceExtensions;
	VkInstance instance = VK_NULL_HANDLE;
};