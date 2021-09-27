#pragma once
#include <vector>

#include "vulkan/vulkan.h"
#include <string>
#include "Class/ClassInfo.h"
#include "VulkanDebugLayer.h"
#include "VulkanSurface.h"
#include "VulkanDevice.h"

class VulkanInstance
{
public:
	void Init(HINSTANCE windowInstance, HWND window);
	void Uninit();
	~VulkanInstance();

	DEFINE_GETTER_SETTER(VkInstance, instance);
	
private:
	void CreateInstance();
	void DestroyInstance();
	std::vector<const char*> GetInstanceExtensions();
private:
	std::vector<std::string> supportedInstanceExtensions;
	std::vector<const char*> enabledInstanceExtensions;

	VkInstance instance = VK_NULL_HANDLE;
	VulkanDebugLayer debugLayer;
	VulkanDevice device;
};
