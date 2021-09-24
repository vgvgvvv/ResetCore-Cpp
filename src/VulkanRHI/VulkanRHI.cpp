#include "VulkanRHI.h"
#include "VulkanTools.h"
#include "VulkanInternal/VulkanInstance.h"
#include "VulkanInternal/VulkanDebugLayer.h"
#include "VulkanInternal/VulkanSurface.h"

void VulkanRHI::InitSingleton()
{
	instance = new VulkanInstance;
	debugLayer = new VulkanDebugLayer;
	surface = new VulkanSurface;
}

void VulkanRHI::Init(HINSTANCE windowInstance, HWND window)
{
	instance->Init();
	debugLayer->Init(instance->get_instance());
	surface->Init(instance->get_instance(), windowInstance, window);

}

void VulkanRHI::Uninit()
{
	surface->Uninit(instance->get_instance());
	DELETE_AND_SET_NULLPTR(surface);
	
	debugLayer->Uninit(instance->get_instance());
	DELETE_AND_SET_NULLPTR(debugLayer);
	
	instance->Uninit();
	DELETE_AND_SET_NULLPTR(instance);
}
