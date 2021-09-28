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
	ComPtr<IDXGISwapChain> SwapChain;                  // D3D11������
	ComPtr<IDXGISwapChain1> SwapChain1;                // D3D11.1������

private:
	// ������Դ
	ComPtr<ID3D11Texture2D> DepthStencilBuffer;        // ���ģ�建����
	ComPtr<ID3D11RenderTargetView> RenderTargetView;   // ��ȾĿ����ͼ
	ComPtr<ID3D11DepthStencilView> DepthStencilView;   // ���ģ����ͼ
	D3D11_VIEWPORT ScreenViewport;                      // �ӿ�

private:
	D3D11Device* owner;
};
