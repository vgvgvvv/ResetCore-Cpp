#pragma once
#include <string>

#include "vulkan/vulkan.h"
#include "Logging/Log.h"
#if PLATFORM_WINDOWS
#include <windows.h>
#endif

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

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			// ��һ�������������ԣ�
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: �����Ϣ
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT����Ϣ����Ϣ���紴����Դ
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT�����ڲ�һ���Ǵ������Ϊ����Ϣ�����ܿ���������Ӧ�ó����еĴ���
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT���й���Ч�ҿ��ܵ��±�������Ϊ����Ϣ
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			// VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: ������һЩ����������޹ص��¼�
			// VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: ������Υ���淶��������ܴ��ڴ��������
			// VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT��Vulkan ��Ǳ�ڷ����ʹ��
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			// ��pCallbackData����ָ����һ��VkDebugUtilsMessengerCallbackDataEXT������Ϣ������ϸ��Ϣ�Ľṹ��
			// pMessage: ��Ϊ�Կ��ַ���β���ַ����ĵ�����Ϣ
			// pObjects������Ϣ��ص� Vulkan ����������
			// objectCount: �����еĶ�����
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			// ��󣬸�pUserData��������һ���ڻص������ڼ�ָ����ָ�룬�����������Լ������ݴ��ݸ�����
			void* pUserData
		)
		{
			RE_LOG_ERROR("Vulkan", "validation layer: {0}", pCallbackData->pMessage);
			return VK_FALSE;
		}

		
		inline VkDebugUtilsMessengerCreateInfoEXT CreateVkDebugUtilsMessengerCreateInfoEXT(PFN_vkDebugUtilsMessengerCallbackEXT callback = debugCallback)
		{
			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

			debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			// ������
			debugCreateInfo.messageSeverity =
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			// ����
			debugCreateInfo.messageType =
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debugCreateInfo.pfnUserCallback = callback;
			
			return debugCreateInfo;
		}

#if PLATFORM_WINDOWS
		inline VkWin32SurfaceCreateInfoKHR CreateVkWin32SurfaceCreateInfoKHR(HINSTANCE platformHandle, HWND platformWindow)
		{
			VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
			surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.hinstance = (HINSTANCE)platformHandle;
			surfaceCreateInfo.hwnd = (HWND)platformWindow;
			return surfaceCreateInfo;
		}
#endif
		
		
	}
}
