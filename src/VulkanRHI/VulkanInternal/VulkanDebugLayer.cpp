#include "VulkanDebugLayer.h"
#include "Misc/GlobalContext.h"
#include "VulkanInitializers.h"
#include "VulkanTools.h"

using namespace VKRHI::Initializers;

void VulkanDebugLayer::Init(VkInstance instance)
{
	static bool enableValidationLayers = GlobalContext::Get().GetBoolValue("vulkan.enableValidationLayers");
	if(!enableValidationLayers)
	{
		return;
	}
	auto createInfo = CreateVkDebugUtilsMessengerCreateInfoEXT();

	VK_CHECK_RESULT(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger));
	
}

void VulkanDebugLayer::Uninit(VkInstance instance)
{
	static bool enableValidationLayers = GlobalContext::Get().GetBoolValue("vulkan.enableValidationLayers");
	if(enableValidationLayers)
	{
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}
}

VkResult VulkanDebugLayer::CreateDebugUtilsMessengerEXT(VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	// ��ȡ��չ������ַ
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else
	{
		// �޷���ȡ����չ����
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void VulkanDebugLayer::DestroyDebugUtilsMessengerEXT(VkInstance instance,
	VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr)
	{
		func(instance, debugMessenger, pAllocator);
	}
}

bool VulkanDebugLayer::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	// ����������Ҫ��ÿ��Layer�鿴�Ƿ����
	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;
		for (const auto& layerProperies : availableLayers)
		{
			if (strcmp(layerName, layerProperies.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}
	return true;
}
