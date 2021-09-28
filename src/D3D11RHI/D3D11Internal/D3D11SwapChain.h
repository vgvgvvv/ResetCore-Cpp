#pragma once
#include "D3D11Utils.h"

class D3D11Device;

class D3D11SwapChain
{
public:
	void Init(D3D11Device* owner);
	void OnResize();
	void Uninit();

	DEFINE_GETTER(ComPtr<IDXGISwapChain>, SwapChain);
	DEFINE_GETTER(ComPtr<IDXGISwapChain1>, SwapChain1);
private:
	void CreateSwapChain();

private:
	ComPtr<IDXGISwapChain> SwapChain;                  // D3D11交换链
	ComPtr<IDXGISwapChain1> SwapChain1;                // D3D11.1交换链

private:
	// 常用资源
	ComPtr<ID3D11Texture2D> DepthStencilBuffer;        // 深度模板缓冲区
	ComPtr<ID3D11RenderTargetView> RenderTargetView;   // 渲染目标视图
	ComPtr<ID3D11DepthStencilView> DepthStencilView;   // 深度模板视图
	D3D11_VIEWPORT ScreenViewport;                      // 视口

private:
	D3D11Device* owner;
};
