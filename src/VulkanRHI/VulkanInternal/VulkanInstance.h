#pragma once
#include <vector>

#include "vulkan/vulkan.h"
#include <string>
#include "Class/ClassInfo.h"

class VulkanInstance
{
public:
	void Init();
	void Uninit();
	~VulkanInstance();

	DEFINE_GETTER_SETTER(VkInstance, instance);
	
private:
	std::vector<const char*> GetInstanceExtensions();
private:
	std::vector<std::string> supportedInstanceExtensions;
	std::vector<const char*> enabledInstanceExtensions;
	VkInstance instance = VK_NULL_HANDLE;
};
