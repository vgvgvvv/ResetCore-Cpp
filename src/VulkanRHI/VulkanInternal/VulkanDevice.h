#pragma once
#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"
#include "VulkanSwapChain.h"
#include "VulkanSurface.h"
#include <optional>


class VulkanInstance;

// 队列族
struct VulkanQueueFamilyIndices
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
	void Init(VulkanInstance* owner, HINSTANCE windowInstance, HWND window);
	void Uninit();
	
	VulkanQueueFamilyIndices FindQueueFamilies();
	SwapChainSupportDetails QuerySwapChainSupport();
	
	DEFINE_GETTER(VkPhysicalDevice, physicalDevice);
	DEFINE_GETTER(VkDevice, device);
	DEFINE_GETTER(VulkanSurface, surface);
	DEFINE_GETTER(VulkanSwapChain, swapchain);

protected:
	// 是否是合适的Physic设备
	virtual bool IsDeviceSuitable(VkPhysicalDevice device);
	// 获取设备特性
	virtual VkPhysicalDeviceFeatures GetDeviceFeature();
private:
	void FindPhysicxDevice();
	void CreateLogicDevice();
	void DestroyLogicDevice();
	VulkanQueueFamilyIndices FindQueueFamilies_Internal(VkPhysicalDevice device);
	SwapChainSupportDetails QuerySwapChainSupport_Internal(VkPhysicalDevice device);
private:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;		// 物理设备
	VkDevice device = VK_NULL_HANDLE;						// 物理设备
	VkQueue graphicsQueue = VK_NULL_HANDLE;					// 逻辑图形设备队列

	VulkanSurface surface;									// 窗口Surface
	VkQueue presentQueue = VK_NULL_HANDLE;					// 显示队列
	
	VulkanSwapChain swapchain;								// 交换链

private:
	class VulkanInstance* owner;
};
