#pragma once
#include "vulkan/vulkan.h"
#include "Class/ClassInfo.h"

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

	void Init();
	void Unit();

private:
	void CreateSwapChain();
	void DestroySwapChain();
	
	DEFINE_GETTER(VkSwapchainKHR, swapchain);
private:
	// ������
	VkSwapchainKHR swapchain;
	// ������ͼ��
	std::vector<VkImage> swapChainImages;
	// ��������ʽ
	VkFormat swapChainImageFormat;
	// ��������С
	VkExtent2D swapChainExtent;
};