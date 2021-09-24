#include "VulkanRHI.h"

void VulkanRHI::InitSingleton()
{
}

void VulkanRHI::Init(HINSTANCE windowInstance, HWND window)
{
	instance.Init();
	debugLayer.Init(instance.get_instance());
	surface.Init(instance.get_instance(), windowInstance, window);
}

void VulkanRHI::Uninit()
{
	surface.Uninit(instance.get_instance());
	debugLayer.Uninit(instance.get_instance());
	instance.Uninit();
}
