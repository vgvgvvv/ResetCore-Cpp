#pragma once
#include <vector>
#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

class VulkanDebugLayer
{
public:
	void Init(VkInstance instance);
	void Uninit(VkInstance instance);

	DEFINE_GETTER_SETTER(VkDebugUtilsMessengerEXT, debugMessenger);

private:
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instrance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger);

	void DestroyDebugUtilsMessengerEXT(VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	bool CheckValidationLayerSupport();
	
	VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
};