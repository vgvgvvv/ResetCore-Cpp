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

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			// 第一个参数是严重性：
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: 诊断信息
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT：信息性消息，如创建资源
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT：关于不一定是错误的行为的消息，但很可能是您的应用程序中的错误
			// VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT：有关无效且可能导致崩溃的行为的消息
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			// VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: 发生了一些与规格或性能无关的事件
			// VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: 发生了违反规范或表明可能存在错误的事情
			// VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT：Vulkan 的潜在非最佳使用
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			// 该pCallbackData参数指的是一个VkDebugUtilsMessengerCallbackDataEXT包含消息本身详细信息的结构体
			// pMessage: 作为以空字符结尾的字符串的调试消息
			// pObjects：与消息相关的 Vulkan 对象句柄数组
			// objectCount: 数组中的对象数
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			// 最后，该pUserData参数包含一个在回调设置期间指定的指针，并允许您将自己的数据传递给它。
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
			// 严重性
			debugCreateInfo.messageSeverity =
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			// 类型
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
