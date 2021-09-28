#include "VulkanRHILayer.h"
#include "VulkanRHI.h"
#if PLATFORM_WINDOWS
#include <windows.h>
#endif

void VulkanRHILayer::OnInit()
{
	VulkanWindowInfo info;
	info.windowInstance = windowLayer->get_appInstance();
	info.window = windowLayer->get_mhMainWnd();
#if PLATFORM_WINDOWS
	info.width = windowLayer->get_width();
	info.height = windowLayer->get_height();
#endif
	VulkanRHI::Get().Init(info);
}

void VulkanRHILayer::OnShutDown()
{
	VulkanRHI::Get().Uninit();
}
