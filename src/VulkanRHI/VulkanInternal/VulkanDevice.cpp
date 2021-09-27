#include "VulkanDevice.h"

void VulkanDevice::Init(const VulkanInstance* owner,  HINSTANCE windowInstance, HWND window)
{
	this->owner = owner;
	surface.Init(owner->get_instance(), windowInstance, window);
	CreateLogicDevice();
}

void VulkanDevice::Uninit()
{
}


QueueFamilyIndices VulkanDevice::FindQueueFamilies()
{
	return FindQueueFamilies_Internal(physicalDevice);
}

bool VulkanDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
}

QueueFamilyIndices VulkanDevice::FindQueueFamilies_Internal(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	// ��ȡQueue Family����
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		// ��Ҫ֧��ͼ��
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}

		// ��Ҫ����֧��
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface.get_surface(), &presentSupport);

		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		// ���϶�֧�ֵ�������˳�
		if (indices.IsComplete())
		{
			break;
		}

		i++;
	}

	return indices;
}

void VulkanDevice::CreateLogicDevice()
{
	
}
