#pragma once
#include "vulkan/vulkan.h"
#include "Singleton.h"
#include "VulkanRHI_API.h"

class VulkanRHI_API VulkanRHI
{
	DEFINE_SINGLETON(VulkanRHI)
public:

private:
	void CreateInstance();
    VkInstance instance = VK_NULL_HANDLE; // VkÊµÀý

};