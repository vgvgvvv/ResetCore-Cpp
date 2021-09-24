#include "VulkanRHI.h"

void VulkanRHI::InitSingleton()
{
}

void VulkanRHI::Init()
{
	instance.Init();
	debugLayer.Init(instance.get_instance());
}

void VulkanRHI::Uninit()
{
	debugLayer.Uninit(instance.get_instance());
	instance.Uninit();
}
