#pragma once 
#include "Application/Layer.h"
#include "Layers/WindowLayer.h"

class VulkanRHILayer : public Layer
{
public:
	VulkanRHILayer(WindowLayer* windowLayer)
		: windowLayer(windowLayer)
	{
	}
	void OnInit() override;
	void OnShutDown() override;

private:
	const WindowLayer* windowLayer;

};
