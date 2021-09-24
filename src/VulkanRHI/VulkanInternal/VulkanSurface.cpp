#include "VulkanSurface.h"
#include "VulkanInitializers.h"
#include "VulkanTools.h"

using namespace VKRHI::Initializers;

void VulkanSurface::Init(VkInstance instance, HINSTANCE windowInstance, HWND window)
{
	auto createInfo = CreateVkWin32SurfaceCreateInfoKHR(windowInstance, window);
	VK_CHECK_RESULT(vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface));
}

void VulkanSurface::Uninit(VkInstance instance)
{
	// Ïú»ÙSurface
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
