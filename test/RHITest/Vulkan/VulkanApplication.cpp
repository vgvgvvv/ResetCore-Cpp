#include "VulkanApplication.h"
#include "Layers/WindowLayer.h"
#include "Layers/VulkanRHILayer.h"

void VulkanApplication::Init()
{
	auto windowLayer = new WindowLayer(800, 600, appInstance);
	LayerManager.PushLayer(windowLayer);
	LayerManager.PushLayer(new VulkanRHILayer(windowLayer));
}

void VulkanApplication::Uninit()
{
}
