#include "VulkanInstance.h"


#include <iostream>
#include <vector>

#include "VulkanInitializers.h"
#include "VulkanTools.h"
#include "Logging/Log.h"

using namespace VKRHI::Initializers;
using namespace VKRHI::Tools;

void VulkanInstance::Init()
{
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

	//TODO

	instanceExtensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#if PLATFORM_WINDOWS
	instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif PLATFORM_MACOS
	instanceExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#else
	#error Not Support This Platform
#endif
	
	// 最终创建实例
	// 创建信息	+ 分配器函数 + 储存Instance的指针
	VK_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &instance));
}

VulkanInstance::~VulkanInstance()
{
}
