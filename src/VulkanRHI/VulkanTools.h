#pragma once
#include "vulkan/vulkan.h"
#include <string>
#include <cassert>
#include <vector>
#include <iostream>

#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << VKRHI::Tools::ErrorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << "\n"; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}

#define DELETE_AND_SET_NULLPTR(Var) \
	delete Var;						\
	Var = nullptr;

namespace VKRHI
{
	namespace Tools
	{
		/** @brief Returns an error code as a string */
		std::string ErrorString(VkResult errorCode);

		/** @brief Returns the device type as a string */
		std::string PhysicalDeviceTypeString(VkPhysicalDeviceType type);

		// Selected a suitable supported depth format starting with 32 bit down to 16 bit
		// Returns false if none of the depth formats in the list is supported by the device
		VkBool32 GetSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat* depthFormat);

		// 获取可用的扩展属性
		std::vector<VkExtensionProperties> GetAvailableExtensionProperties();

	}
}
