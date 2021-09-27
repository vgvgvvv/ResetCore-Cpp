#include "VulkanDevice.h"

#include <set>

#include "DeviceExtension.h"
#include "VulkanTools.h"
#include "VulkanInitializers.h"
#include "VulkanInstance.h"
#include "Misc/GlobalContext.h"

using namespace VKRHI::Initializers;

void VulkanDevice::Init(VulkanInstance* owner,  HINSTANCE windowInstance, HWND window)
{
	this->owner = owner;
	surface.Init(owner->get_instance(), windowInstance, window);

	FindPhysicxDevice();
	CreateLogicDevice();

	swapchain.Init();
}

void VulkanDevice::Uninit()
{
	swapchain.Unit();
	DestroyLogicDevice();
	surface.Uninit(owner->get_instance());
}

// ��ȡ���������豸�Ķ���
QueueFamilyIndices VulkanDevice::FindQueueFamilies()
{
	return FindQueueFamilies_Internal(physicalDevice);
}

bool VulkanDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
	// ͨ�����·�ʽ����ȡ��Ӧ���豸������Ŀǰ����������Ҫ��ȡ��������Ӧ�豸���е��豸
	// VkPhysicalDeviceProperties deviceProperties;
	// vkGetPhysicalDeviceProperties(device, &deviceProperties);
	// VkPhysicalDeviceFeatures deviceFeatures;
	// vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	//
	// return deviceProperties.deviceType == 
	// 	VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
	// 	deviceFeatures.geometryShader;

	auto family = FindQueueFamilies_Internal(device);

	bool extensionSupport = VKRHI::Tools::CheckDeviceExtensionSupport(device);

	bool swapChainAdequate = false;
	if (extensionSupport)
	{
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats.empty() &&
			!swapChainSupport.presentModes.empty();
	}

	return family.IsComplete() && extensionSupport && swapChainAdequate;
}

VkPhysicalDeviceFeatures VulkanDevice::GetDeviceFeature()
{
	// ָ�����ܼ�
	VkPhysicalDeviceFeatures deviceFeatures{};
	return deviceFeatures;
}

void VulkanDevice::FindPhysicxDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(owner->get_instance(), &deviceCount, nullptr);

	// δ�ҵ��κ��豸
	if (deviceCount == 0)
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(owner->get_instance(), &deviceCount, devices.data());

	// �ж��Ƿ����
	for (const auto& device : devices)
	{
		// ����ͨ��������ɸѡӲ����Ҳ����ͨ��������ѡ��
		if (IsDeviceSuitable(device))
		{
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("failed to find a suitable GPU!");
	}
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
		VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface.get_surface(), &presentSupport));

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

// �鿴SwapChain֧�����
SwapChainSupportDetails VulkanDevice::QuerySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;
	auto swapChainSurface = surface.get_surface();
	
	// ���capabilities
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, swapChainSurface, &details.capabilities));

	// ���format
	uint32_t formatCount;
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(device, swapChainSurface, &formatCount, nullptr));

	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(device, swapChainSurface, &formatCount, details.formats.data()));
	}

	// ���present mode
	uint32_t presentModeCount = 0;
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(device, swapChainSurface, &presentModeCount, nullptr));

	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		VK_CHECK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(device, swapChainSurface, &presentModeCount, details.presentModes.data()));
	}

	return details;
}

void VulkanDevice::CreateLogicDevice()
{
	// ��ȡ����֮ǰ�õ��������豸
	QueueFamilyIndices indices = FindQueueFamilies();

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	//��ȡ������Ҫ�Ķ���
	std::set<uint32_t> uniqueQueueFamilies =
	{
		indices.graphicsFamily.value(),
		indices.presentFamily.value()
	};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = CreateVkDeviceQueueCreateInfo(queueFamily, &queuePriority, 1);
		queueCreateInfos.push_back(queueCreateInfo);
	}

	// �����豸
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

	auto deviceInfo = GetDeviceFeature();
	createInfo.pEnabledFeatures = &deviceInfo;

	// ֧�ֵ���չ����
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	static bool enableValidationLayers = GlobalContext::Get().GetBoolValue("vulkan.enableValidationLayers");
	// �µ�Vulkan�Ѿ��������豸���У��㣬���������Ѿ����ϰ汾Vulkan���м���
	if (enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	VK_CHECK_RESULT(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device));

	// �������߼��豸�������塢����������ָ��洢���о���ı�����ָ�롣
	// ��Ϊ����ֻ������崴��һ�����У��������ǽ��򵥵�ʹ������0��
	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);

	vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

void VulkanDevice::DestroyLogicDevice()
{
	// �����߼��豸
	vkDestroyDevice(device, nullptr);
}
