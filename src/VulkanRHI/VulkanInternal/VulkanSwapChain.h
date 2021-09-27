#pragma once
#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"

// SwapChain的功能支持情况
struct SwapChainSupportDetails
{
	// 基本表面功能（交换链中的最小/最大图像数，图像的最小/最大宽度和高度）
	VkSurfaceCapabilitiesKHR capabilities;
	// 表面格式（像素格式、色彩空间）
	std::vector<VkSurfaceFormatKHR> formats;
	// 可用的演示模式
	std::vector<VkPresentModeKHR> presentModes;
};


class VulkanSwapChain
{
public:

	void Init();
	void Unit();

private:
	void CreateSwapChain();
	void DestroySwapChain();
	
	DEFINE_GETTER(VkSwapchainKHR, swapchain);
private:
	// 交换链
	VkSwapchainKHR swapchain;
	// 交换链图像
	std::vector<VkImage> swapChainImages;
	// 交换链格式
	VkFormat swapChainImageFormat;
	// 交换链大小
	VkExtent2D swapChainExtent;
};