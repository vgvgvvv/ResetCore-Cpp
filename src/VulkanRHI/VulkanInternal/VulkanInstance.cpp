#include "VulkanInstance.h"


#include <iostream>
#include <vector>

#include "VulkanInitializers.h"
#include "VulkanTools.h"
#include "Logging/Log.h"
#include "Misc/GlobalContext.h"
#include "VulkanDebugLayer.h"

using namespace VKRHI::Initializers;
using namespace VKRHI::Tools;



void VulkanInstance::Init()
{

	static bool enableValidationLayers = GlobalContext::Get().GetBoolValue("vulkan.enableValidationLayers");
	
	VkApplicationInfo appInfo = 
		CreateVkApplicationInfo("Hello Triangle", "No Engine");

	// Instance 创建信息
	VkInstanceCreateInfo createInfo = CreateVkInstanceCreateInfo(&appInfo);

	auto extensions = GetAvailableExtensionProperties();
	RE_LOG_INFO("Vulkan", "available extensions: ")
	for (const auto& extension : extensions)
	{
		RE_LOG_INFO("Vulkan", "\t{0}", extension.extensionName)
	}

	// 获取可用的扩展
	auto instanceExtensions = GetInstanceExtensions();

	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();

	// 初始化验证层
	if(enableValidationLayers)
	{
		auto debugCreateInfo = CreateVkDebugUtilsMessengerCreateInfoEXT();
		createInfo.enabledLayerCount = validationLayers.size();
		createInfo.ppEnabledLayerNames = validationLayers.data();
		createInfo.pNext = &debugCreateInfo;
	}else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}
	
	// 最终创建实例
	// 创建信息	+ 分配器函数 + 储存Instance的指针
	VK_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &instance));
}

void VulkanInstance::Uninit()
{
	// 销毁实例
	vkDestroyInstance(instance, nullptr);
}


std::vector<const char*> VulkanInstance::GetInstanceExtensions()
{
	std::vector<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME };
	
	// Enable surface extensions depending on os
#if defined(_WIN32)
	instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
	instanceExtensions.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_DIRECT2DISPLAY)
	instanceExtensions.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_DIRECTFB_EXT)
	instanceExtensions.push_back(VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
	instanceExtensions.push_back(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
	instanceExtensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	instanceExtensions.push_back(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	instanceExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_HEADLESS_EXT)
	instanceExtensions.push_back(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
#endif

	// Get extensions supported by the instance and store for later use
	uint32_t extCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
	if (extCount > 0)
	{
		std::vector<VkExtensionProperties> extensions(extCount);
		if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, &extensions.front()) == VK_SUCCESS)
		{
			for (VkExtensionProperties extension : extensions)
			{
				supportedInstanceExtensions.push_back(extension.extensionName);
			}
		}
	}

	// Enabled requested instance extensions
	if (enabledInstanceExtensions.size() > 0)
	{
		for (const char* enabledExtension : enabledInstanceExtensions)
		{
			// Output message if requested extension is not available
			if (std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), enabledExtension) == supportedInstanceExtensions.end())
			{
				RE_LOG_ERROR("Vulkan", "Enabled instance extension \"{0}\" is not present at instance level", enabledExtension);
			}
			instanceExtensions.push_back(enabledExtension);
		}
	}

	if (instanceExtensions.size() > 0)
	{
		static bool enableValidationLayers = GlobalContext::Get().GetBoolValue("vulkan.enableValidationLayers");
		if (enableValidationLayers)
		{
			instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}
	}

	return instanceExtensions;
}

VulkanInstance::~VulkanInstance()
{
	
}
