#include "VulkanSwapChain.h"
#include <algorithm>
#include <QueueFamily.h>
#include "VulkanDevice.h"
#include "VulkanRHI.h"
#include "VulkanTools.h"


void VulkanSwapChain::Init(VulkanDevice* owner)
{
	this->owner = owner;
	CreateSwapChain();
	CreateImageView();
}

void VulkanSwapChain::Uninit()
{
	DestroyImageView();
	DestroySwapChain();
}

void VulkanSwapChain::CreateSwapChain()
{
	SwapChainSupportDetails support = owner->QuerySwapChainSupport();

	VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(support.formats);
	VkPresentModeKHR presentMode = ChooseSwapPresentMode(support.presentModes);
	
	auto windowInfo = VulkanRHI::Get().get_windowInfo();
	VkExtent2D extent = ChooseSwapExtent(support.capabilities, windowInfo.width, windowInfo.height);

	//  然而，简单地坚持这个最小值意味着我们有时可能不得不等待驱动程序完成内部操
	// 作，然后才能获取另一个图像进行渲染。因此，建议请求至少比最小值多一张图像：
	uint32_t imageCount = support.capabilities.minImageCount + 1;

	// 保证最大数量
	if (support.capabilities.maxImageCount > 0 && imageCount > support.capabilities.maxImageCount) {
		imageCount = support.capabilities.maxImageCount;
	}

	// 创建SwapChain
	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = owner->get_surface().get_surface();
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	// imageArrayLayers指定层的每个图像包括的量。
	// 1除非您正在开发立体 3D 应用程序，否则始终如此
	createInfo.imageArrayLayers = 1;
	// 
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	VulkanQueueFamilyIndices indices = owner->FindQueueFamilies();
	uint32_t queueFamilyIndices[] = {
		indices.graphicsFamily.value(),
		indices.presentFamily.value()
	};

	/*
	 * VK_SHARING_MODE_EXCLUSIVE：一个图像一次由一个队列家族拥有，并且在另一个队
	 * 列家族中使用它之前必须明确转移所有权。此选项可提供最佳性能。
	 * VK_SHARING_MODE_CONCURRENT：图像可以跨多个队列系列使用，无需明确的所有权
	 * 转移。
	 */
	if (indices.graphicsFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	// 支持画面图像应用某种变换，比如旋转
	createInfo.preTransform = support.capabilities.currentTransform;
	// 是否使用Alpha通道和窗口系统中其他窗口混合
	// VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR 忽略Alpha通道
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	createInfo.presentMode = presentMode;
	// 裁切不可见元素
	createInfo.clipped = VK_TRUE;
	/*
	 * 使用 Vulkan 时，您的交换链可能会在您的应用程序运行时变得无效或未优化，例如
	 * 因为窗口已调整大小。在这种情况下，交换链实际上需要从头开始重新创建，并且必
	 * 须在此字段中指定对旧链的引用。这是一个复杂的主题，我们将在以后的章节中详细
	 * 了解。现在我们假设我们只会创建一个交换链。
	 */
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	auto device = owner->get_device();
	VK_CHECK_RESULT(vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain));

	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr));
	swapChainImages.resize(imageCount);
	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapChainImages.data()));

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;
}

void VulkanSwapChain::DestroySwapChain()
{
	// 销毁SwapChain
	vkDestroySwapchainKHR(owner->get_device(), swapchain, nullptr);
}


void VulkanSwapChain::CreateImageView()
{
}

void VulkanSwapChain::DestroyImageView()
{
}

void VulkanSwapChain::CreateFramebuffer()
{
}

void VulkanSwapChain::DestroyFramebuffer()
{
}

VkSurfaceFormatKHR VulkanSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	/*
	 * 每个VkSurfaceFormatKHR条目包含一个format和一个colorSpace成员。该 format
	 * 成员指定颜色通道和类型。例如， VK_FORMAT_B8G8R8A8_SRGB意味着我们以 8 位无
	 * 符号整数的顺序存储 B、G、R 和 alpha 通道，每个像素总共 32 位。该
	 * colorSpace成员使用VK_COLOR_SPACE_SRGB_NONLINEAR_KHR标志指示是否支持 SRGB
	 * 颜色空间。请注意，该标志曾经VK_COLORSPACE_SRGB_NONLINEAR_KHR在旧版本的规
	 * 范中被调用。
	 */

	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR VulkanSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	/*
	 * VK_PRESENT_MODE_IMMEDIATE_KHR：您的应用程序提交的图像会立即传输到屏幕上，
	 * 这可能会导致撕裂。
	 *
	 * VK_PRESENT_MODE_FIFO_KHR：交换链是一个队列，当显示器刷新时，显示器从队
	 * 前面获取图像，程序在队列后面插入渲染图像。如果队列已满，则程序必须等待。
	 * 与现代游戏中的垂直同步最为相似。显示刷新的那一刻被称为“垂直空白”。
	 *
	 * VK_PRESENT_MODE_FIFO_RELAXED_KHR：此模式仅在申请延迟且队列在最后一个垂
	 * 空白时为空时与前一种模式不同。图像最终到达时立即传输，而不是等待下一个垂
	 * 直空白。这可能会导致可见的撕裂。
	 *
	 * VK_PRESENT_MODE_MAILBOX_KHR：这是第二种模式的另一种变体。当队列已满时，
	 * 不会阻塞应用程序，而是将已经排队的图像简单地替换为较新的图像。此模式可用
	 * 于在避免撕裂的同时尽可能快地渲染帧，从而导致比标准垂直同步更少的延迟问题
	 * 。这就是俗称的“三重缓冲”，尽管单独存在三个缓冲并不一定意味着帧率已解锁。
	 */

	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D VulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, int width, int height)
{
	if (capabilities.currentExtent.width != UINT32_MAX)
	{
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);

		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height,
			capabilities.maxImageExtent.height);

		return actualExtent;

	}
}
