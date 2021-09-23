#pragma once
#include <string>

#include "vulkan/vulkan.h"

namespace VKRHI
{
	namespace Initializers
	{
		inline VkApplicationInfo CreateVkApplicationInfo(const char* appName, const char* engineName)
		{
			// Program Info
			// 用于部分驱动对于特定引擎或者程序的优化
			VkApplicationInfo appInfo = {};
			// 指定Info类型
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = appName;
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = engineName;
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			return appInfo;
		}

		inline VkInstanceCreateInfo CreateVkInstanceCreateInfo(const VkApplicationInfo* appInfo)
		{
			// Instance 创建信息
			VkInstanceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = appInfo;
			return createInfo;
		}

		
	}
}
