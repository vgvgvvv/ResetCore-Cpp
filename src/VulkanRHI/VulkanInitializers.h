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
			// ���ڲ������������ض�������߳�����Ż�
			VkApplicationInfo appInfo = {};
			// ָ��Info����
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
			// Instance ������Ϣ
			VkInstanceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = appInfo;
			return createInfo;
		}

		
	}
}
