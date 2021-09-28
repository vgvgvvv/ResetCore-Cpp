#include "D3D12Application.h"
#include "Layers/WindowLayer.h"
#include "Layers/D3D12RHILayer.h"

void D3D12Application::Init()
{
	auto windowLayer = new WindowLayer(800, 600, appInstance);
	LayerManager.PushLayer(windowLayer);
	LayerManager.PushLayer(new D3D12RHILayer(windowLayer));
}

void D3D12Application::Uninit()
{
}
