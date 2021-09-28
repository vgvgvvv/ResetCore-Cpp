#pragma once
#include "D3D11SwapChain.h"
#include "D3D11Utils.h"

class D3D11Device
{
public:
	D3D11Device()
	{
		swapchain = std::make_shared<D3D11SwapChain>();
	}
	void Init();
	void OnResize();
	void Uninit();

	DEFINE_GETTER(ComPtr<ID3D11Device>, d3dDevice);
	DEFINE_GETTER(ComPtr<ID3D11Device1>, d3dDevice1);
	DEFINE_GETTER(ComPtr<ID3D11DeviceContext>, d3dImmediateContext);
	DEFINE_GETTER(ComPtr<ID3D11DeviceContext1>, d3dImmediateContext1);
	DEFINE_GETTER(UINT, Msaa4xQuality)
private:
	void CreateDevice();

private:
	// Direct3D 11
	ComPtr<ID3D11Device> d3dDevice;                    // D3D11设备
	ComPtr<ID3D11DeviceContext> d3dImmediateContext;   // D3D11设备上下文
	// Direct3D 11.1
	ComPtr<ID3D11Device1> d3dDevice1;                  // D3D11.1设备
	ComPtr<ID3D11DeviceContext1> d3dImmediateContext1; // D3D11.1设备上下文

	UINT      Msaa4xQuality;   // MSAA支持的质量等级

private:

	std::shared_ptr<D3D11SwapChain> swapchain;
};