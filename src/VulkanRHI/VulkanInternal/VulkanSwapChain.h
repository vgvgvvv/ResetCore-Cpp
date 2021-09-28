#pragma once
#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"

class VulkanDevice;

// SwapChain�Ĺ���֧�����
struct SwapChainSupportDetails
{
	// �������湦�ܣ��������е���С/���ͼ������ͼ�����С/����Ⱥ͸߶ȣ�
	VkSurfaceCapabilitiesKHR capabilities;
	// �����ʽ�����ظ�ʽ��ɫ�ʿռ䣩
	std::vector<VkSurfaceFormatKHR> formats;
	// ���õ���ʾģʽ
	std::vector<VkPresentModeKHR> presentModes;
};


class VulkanSwapChain
{
public:

	void Init(VulkanDevice* owner);
	void Uninit();

private:
	void CreateSwapChain();
	void DestroySwapChain();

	void CreateImageView();
	void DestroyImageView();

private:
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, int width, int height);
	
	DEFINE_GETTER(VkSwapchainKHR, swapchain);
	DEFINE_GETTER(std::vector<VkImage>, swapChainImages);
	DEFINE_GETTER(VkFormat, swapChainImageFormat);
	DEFINE_GETTER(std::vector<VkImageView>, swapChainImageViews);
private:
	// ������
	VkSwapchainKHR swapchain;
	// ������ͼ��
	std::vector<VkImage> swapChainImages;
	// ��������ʽ
	VkFormat swapChainImageFormat;
	// ��������С
	VkExtent2D swapChainExtent;

	std::vector<VkImageView> swapChainImageViews;

private:
	VulkanDevice* owner;
};