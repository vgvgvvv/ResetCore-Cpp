#include "D3D11RHI.h"

#include "D3D11Internal/D3D11Device.h"

void D3D11RHI::InitSingleton()
{
	device = std::make_shared<D3D11Device>();
}

void D3D11RHI::Init(D3D11WindowInfo windowInfo)
{
	this->windowInfo = windowInfo;
	device->Init();
}


void D3D11RHI::OnResize()
{
}

void D3D11RHI::Uninit()
{
	device->Uninit();
}
