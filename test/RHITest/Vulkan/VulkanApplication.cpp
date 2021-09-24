#include "VulkanApplication.h"
#include "Layers/WindowLayer.h"

void VulkanApplication::Init()
{
	LayerManager.PushLayer(new WindowLayer(800, 600, appInstance));
}

void VulkanApplication::Uninit()
{
}
