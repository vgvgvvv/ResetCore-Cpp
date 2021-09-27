#include "VulkanRHILayer.h"
#include "VulkanRHI.h"

void VulkanRHILayer::OnInit()
{
	VulkanRHI::Get().Init(appInstance, mhMainWnd);
}

void VulkanRHILayer::OnShutDown()
{
	VulkanRHI::Get().Uninit();
}
