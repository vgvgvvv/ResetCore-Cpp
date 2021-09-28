#pragma once
#include "Application/Layer.h"
#include "Layers/WindowLayer.h"


class D3D12RHILayer : public Layer
{
public:
	D3D12RHILayer(WindowLayer* windowLayer)
		: windowLayer(windowLayer)
	{
	}
	void OnInit() override;
	void OnShutDown() override;

private:
	const WindowLayer* windowLayer;

};
