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

// 获取用于物理设备的队列
QueueFamilyIndices VulkanDevice::FindQueueFamilies()
{
	return FindQueueFamilies_Internal(physicalDevice);
}

bool VulkanDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
	// 通过以下方式来获取相应的设备，但是目前我们真正需要获取的是有相应设备队列的设备
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
	// 指定功能集
	VkPhysicalDeviceFeatures deviceFeatures{};
	return deviceFeatures;
}

void VulkanDevice::FindPhysicxDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(owner->get_instance(), &deviceCount, nullptr);

	// 未找到任何设备
	if (deviceCount == 0)
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(owner->get_instance(), &deviceCount, devices.data());

	// 判断是否可用
	for (const auto& device : devices)
	{
		// 除了通过可用性筛选硬件，也可以通过分数来选择
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

	// 获取Queue Family属性
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		// 需要支持图形
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}

		// 需要窗口支持
		VkBool32 presentSupport = false;
		VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface.get_surface(), &presentSupport));

		if (presentSupport)
		{
			indices.presentFamily = i;
		}

		// 以上都支持的情况下退出
		if (indices.IsComplete())
		{
			break;
		}

		i++;
	}

	return indices;
}

// 查看SwapChain支持情况
SwapChainSupportDetails VulkanDevice::QuerySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;
	auto swapChainSurface = surface.get_surface();
	
	// 填充capabilities
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, swapChainSurface, &details.capabilities));

	// 填充format
	uint32_t formatCount;
	VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(device, swapChainSurface, &formatCount, nullptr));

	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		VK_CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(device, swapChainSurface, &formatCount, details.formats.data()));
	}

	// 填充present mode
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
	// 获取我们之前得到的物理设备
	QueueFamilyIndices indices = FindQueueFamilies();

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	//获取所有需要的队列
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

	// 创建设备
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

	auto deviceInfo = GetDeviceFeature();
	createInfo.pEnabledFeatures = &deviceInfo;

	// 支持的扩展数量
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	static bool enableValidationLayers = GlobalContext::Get().GetBoolValue("vulkan.enableValidationLayers");
	// 新的Vulkan已经忽略了设备层的校验层，但是我们已经对老版本Vulkan进行兼容
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

	// 参数是逻辑设备、队列族、队列索引和指向存储队列句柄的变量的指针。
	// 因为我们只从这个族创建一个队列，所以我们将简单地使用索引0。
	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);

	vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}

void VulkanDevice::DestroyLogicDevice()
{
	// 销毁逻辑设备
	vkDestroyDevice(device, nullptr);
}
