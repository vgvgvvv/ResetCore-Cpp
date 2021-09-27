#include "VulkanTools.h"

#include <vector>
#include "DeviceExtension.h"
#include <set>
#include "CommonAssert.h"

namespace VKRHI
{
	namespace Tools
	{
		std::string VKRHI::Tools::ErrorString(VkResult errorCode)
		{
			switch (errorCode)
			{
#define STR(r) case VK_ ##r: return #r
				STR(NOT_READY);
				STR(TIMEOUT);
				STR(EVENT_SET);
				STR(EVENT_RESET);
				STR(INCOMPLETE);
				STR(ERROR_OUT_OF_HOST_MEMORY);
				STR(ERROR_OUT_OF_DEVICE_MEMORY);
				STR(ERROR_INITIALIZATION_FAILED);
				STR(ERROR_DEVICE_LOST);
				STR(ERROR_MEMORY_MAP_FAILED);
				STR(ERROR_LAYER_NOT_PRESENT);
				STR(ERROR_EXTENSION_NOT_PRESENT);
				STR(ERROR_FEATURE_NOT_PRESENT);
				STR(ERROR_INCOMPATIBLE_DRIVER);
				STR(ERROR_TOO_MANY_OBJECTS);
				STR(ERROR_FORMAT_NOT_SUPPORTED);
				STR(ERROR_SURFACE_LOST_KHR);
				STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
				STR(SUBOPTIMAL_KHR);
				STR(ERROR_OUT_OF_DATE_KHR);
				STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
				STR(ERROR_VALIDATION_FAILED_EXT);
				STR(ERROR_INVALID_SHADER_NV);
#undef STR
			default:
				return "UNKNOWN_ERROR";
			}
		}

		std::string VKRHI::Tools::PhysicalDeviceTypeString(VkPhysicalDeviceType type)
		{
			switch (type)
			{
#define STR(r) case VK_PHYSICAL_DEVICE_TYPE_ ##r: return #r
				STR(OTHER);
				STR(INTEGRATED_GPU);
				STR(DISCRETE_GPU);
				STR(VIRTUAL_GPU);
				STR(CPU);
#undef STR
			default: return "UNKNOWN_DEVICE_TYPE";
			}
		}

		VkBool32 VKRHI::Tools::GetSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat* depthFormat)
		{
			// Since all depth formats may be optional, we need to find a suitable depth format to use
			// Start with the highest precision packed format
			std::vector<VkFormat> depthFormats = {
				VK_FORMAT_D32_SFLOAT_S8_UINT,
				VK_FORMAT_D32_SFLOAT,
				VK_FORMAT_D24_UNORM_S8_UINT,
				VK_FORMAT_D16_UNORM_S8_UINT,
				VK_FORMAT_D16_UNORM
			};

			for (auto& format : depthFormats)
			{
				VkFormatProperties formatProps;
				vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);
				// Format must support depth stencil attachment for optimal tiling
				if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
				{
					*depthFormat = format;
					return true;
				}
			}

			return false;
		}

		std::vector<VkExtensionProperties> GetAvailableExtensionProperties()
		{
			// 输出可用的Vulkan扩展
			uint32_t extensionCount = 0;
			VK_CHECK_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount
				, nullptr));
			std::vector<VkExtensionProperties> extensions(extensionCount);
			VK_CHECK_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()));

			return extensions;
		}


		bool CheckDeviceExtensionSupport(VkPhysicalDevice device)
		{
			uint32_t extensionCount;
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

			std::vector<VkExtensionProperties> availableDeviceExtensions(extensionCount);
			vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableDeviceExtensions.data());

			std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

			// 查看是否所有需要的扩展都能够找到
			for (const auto& extension : availableDeviceExtensions)
			{
				requiredExtensions.erase(extension.extensionName);
			}

			return requiredExtensions.empty();
		}

		VkResult GetPhysicalDevice(VkInstance instance, VkPhysicalDevice& resultDevice, IsDeviceSuitableFunc isDeviceSuitable)
		{
			uint32_t deviceCount = 0;
			VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr));

			// 未找到任何设备
			RE_ASSERT_MSG(deviceCount != 0, "failed to find GPUs with Vulkan support!")

				std::vector<VkPhysicalDevice> devices(deviceCount);
			VK_CHECK_RESULT(vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data()));

			// 判断是否可用
			for (const auto& device : devices)
			{
				// 除了通过可用性筛选硬件，也可以通过分数来选择
				if (isDeviceSuitable(device))
				{
					resultDevice = device;
					break;
				}
			}

			RE_ASSERT_MSG(resultDevice != VK_NULL_HANDLE, "failed to find a suitable GPU!")

				return VkResult::VK_SUCCESS;
		}
	}
}
