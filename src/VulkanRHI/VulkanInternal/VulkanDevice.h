#pragma once
#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"
#include "VulkanSwapChain.h"
#include "VulkanSurface.h"
#include <optional>


class VulkanInstance;

// ������
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
	// �Ƿ��Ǻ��ʵ�Physic�豸
	virtual bool IsDeviceSuitable(VkPhysicalDevice device);
	// ��ȡ�豸����
	virtual VkPhysicalDeviceFeatures GetDeviceFeature();
private:
	void FindPhysicxDevice();
	void CreateLogicDevice();
	void DestroyLogicDevice();
	VulkanQueueFamilyIndices FindQueueFamilies_Internal(VkPhysicalDevice device);
	SwapChainSupportDetails QuerySwapChainSupport_Internal(VkPhysicalDevice device);
private:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;		// �����豸
	VkDevice device = VK_NULL_HANDLE;						// �����豸
	VkQueue graphicsQueue = VK_NULL_HANDLE;					// �߼�ͼ���豸����

	VulkanSurface surface;									// ����Surface
	VkQueue presentQueue = VK_NULL_HANDLE;					// ��ʾ����
	
	VulkanSwapChain swapchain;								// ������

private:
	class VulkanInstance* owner;
};
