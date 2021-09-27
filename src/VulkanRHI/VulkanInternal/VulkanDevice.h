#pragma once
#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"
#include "VulkanSwapChain.h"
#include <optional>
#include "VulkanInstance.h"

// ¶ÓÁÐ×å
struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool IsComplete() const
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class VulkanDevice
{
public:
	void Init(const VulkanInstance* owner, HINSTANCE windowInstance, HWND window);
	void Uninit();
	
	QueueFamilyIndices FindQueueFamilies();
	
	DEFINE_GETTER(VkPhysicalDevice, physicalDevice);
	DEFINE_GETTER(VkDevice, device);

protected:
	virtual bool IsDeviceSuitable(VkPhysicalDevice device);

private:
	void CreateLogicDevice();
	QueueFamilyIndices FindQueueFamilies_Internal(VkPhysicalDevice device);
private:
	VkPhysicalDevice physicalDevice;
	VkDevice device;

	VulkanSurface surface;
	VulkanSwapChain swapchain;

private:
	const VulkanInstance* owner;
};
