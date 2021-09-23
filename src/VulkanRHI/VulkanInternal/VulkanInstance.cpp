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

	// Instance ������Ϣ
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
	
	// ���մ���ʵ��
	// ������Ϣ	+ ���������� + ����Instance��ָ��
	VK_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &instance));
}

VulkanInstance::~VulkanInstance()
{
}
