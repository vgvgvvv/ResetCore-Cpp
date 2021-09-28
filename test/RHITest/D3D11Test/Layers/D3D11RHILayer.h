#pragma once
#include "Application/Layer.h"
#include "Layers/WindowLayer.h"


class D3D11RHILayer : public Layer
{
public:
	D3D11RHILayer(WindowLayer* windowLayer)
		: windowLayer(windowLayer)
	{
	}
	void OnInit() override;
	void OnShutDown() override;

private:
	const WindowLayer* windowLayer;

};
