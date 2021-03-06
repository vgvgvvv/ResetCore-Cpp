#include "VulkanRHI.h"
#include "VulkanTools.h"
#include "VulkanInternal/VulkanInstance.h"
#include "VulkanInternal/VulkanDebugLayer.h"
#include "VulkanInternal/VulkanSurface.h"
#include "VulkanInternal/VulkanDevice.h"

void VulkanRHI::InitSingleton()
{
	instance = new VulkanInstance;
}

void VulkanRHI::Init(VulkanWindowInfo windowInfo)
{
	this->windowInfo = windowInfo;
	instance->Init(windowInfo.windowInstance, windowInfo.window);
}

void VulkanRHI::Uninit()
{
	instance->Uninit();
	DELETE_AND_SET_NULLPTR(instance);
}
