#include "D3D11Application.h"
#include "Layers/WindowLayer.h"
#include "Layers/D3D11RHILayer.h"

void ::D3D11Application::Init()
{
	auto windowLayer = new WindowLayer(800, 600, appInstance);
	LayerManager.PushLayer(windowLayer);
	LayerManager.PushLayer(new D3D11RHILayer(windowLayer));
}

void ::D3D11Application::Uninit()
{
}
