#pragma once
#include "VulkanRHI_API.h"
#include "vulkan/vulkan.h"

struct VulkanRHI_API VulkanBuffer
{
	VkBuffer buffer;
	VkDeviceMemory bufferMemory;
};