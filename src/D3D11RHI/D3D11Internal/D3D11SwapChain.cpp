#include "D3D11SwapChain.h"
#include "D3D11Device.h"
#include "D3D11RHI.h"
#include "Misc/GlobalContext.h"

using namespace D3D11::Initializer;

void D3D11SwapChain::Init(D3D11Device* owner)
{
	RE_LOG_INFO("D3D11", "InitSwapChain");
	this->owner = owner;
	CreateSwapChain();
}

void D3D11SwapChain::OnResize()
{
	// 释放渲染管线输出用到的相关资源
	RenderTargetView.Reset();
	DepthStencilView.Reset();
	DepthStencilBuffer.Reset();

	// 重设交换链并且重新创建渲染目标视图
	ComPtr<ID3D11Texture2D> backBuffer;
	auto windowInfo = D3D11RHI::Get().get_windowInfo();
	HR(SwapChain->ResizeBuffers(1, windowInfo.width, windowInfo.height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	HR(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
	HR(owner->get_d3dDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, RenderTargetView.GetAddressOf()));

	// 设置调试对象名
	D3D11SetDebugObjectName(backBuffer.Get(), "BackBuffer[0]");

	backBuffer.Reset();

	D3D11_TEXTURE2D_DESC depthStencilDesc = CreateDepthStencilTextureDesc(windowInfo, owner->get_Msaa4xQuality());

	// 创建深度缓冲区以及深度模板视图
	HR(owner->get_d3dDevice()->CreateTexture2D(&depthStencilDesc, nullptr, DepthStencilBuffer.GetAddressOf()));
	HR(owner->get_d3dDevice()->CreateDepthStencilView(DepthStencilBuffer.Get(), nullptr, DepthStencilView.GetAddressOf()));

	// 将渲染目标视图和深度/模板缓冲区结合到管线
	owner->get_d3dImmediateContext()->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());

	// 设置视口变换
	ScreenViewport.TopLeftX = 0;
	ScreenViewport.TopLeftY = 0;
	ScreenViewport.Width = static_cast<float>(windowInfo.width);
	ScreenViewport.Height = static_cast<float>(windowInfo.height);
	ScreenViewport.MinDepth = 0.0f;
	ScreenViewport.MaxDepth = 1.0f;

	owner->get_d3dImmediateContext()->RSSetViewports(1, &ScreenViewport);

	// 设置调试对象名
	D3D11SetDebugObjectName(DepthStencilBuffer.Get(), "DepthStencilBuffer");
	D3D11SetDebugObjectName(DepthStencilView.Get(), "DepthStencilView");
	D3D11SetDebugObjectName(RenderTargetView.Get(), "BackBufferRTV[0]");
}

void D3D11SwapChain::Uninit()
{
	RE_LOG_INFO("D3D11", "UninitSwapchain");
}

void D3D11SwapChain::CreateSwapChain()
{
	HRESULT hr = S_OK;
	ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
	ComPtr<IDXGIFactory1> dxgiFactory1 = nullptr;	// D3D11.0(包含DXGI1.1)的接口类
	ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;	// D3D11.1(包含DXGI1.2)特有的接口类

	// 为了正确创建 DXGI交换链，首先我们需要获取创建 D3D设备 的 DXGI工厂，否则会引发报错：
	// "IDXGIFactory::CreateSwapChain: This function is being called with a device from a different IDXGIFactory."
	HR(owner->get_d3dDevice().As(&dxgiDevice));
	HR(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1.GetAddressOf())));

	// 查看该对象是否包含IDXGIFactory2接口
	hr = dxgiFactory1.As(&dxgiFactory2);

	auto windowInfo = D3D11RHI::Get().get_windowInfo();
	static auto enableMsaa = GlobalContext::Get().GetBoolValue("d3d11.enable4xMSAA", false);
	
	// 如果包含，则说明支持D3D11.1
	if (dxgiFactory2 != nullptr)
	{
		auto d3dDevice = owner->get_d3dDevice();
		auto d3dImmediateContext = owner->get_d3dImmediateContext();
		auto d3dDevice1 = owner->get_d3dDevice1();
		auto d3dImmediateContext1 = owner->get_d3dImmediateContext1();
		
		HR(d3dDevice.As(&d3dDevice1));
		HR(d3dImmediateContext.As(&d3dImmediateContext1));
		// 填充各种结构体用以描述交换链
		DXGI_SWAP_CHAIN_DESC1 sd = 
			CreateDXGISwapChainDesc1(windowInfo, owner->get_Msaa4xQuality());

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd = CreateDXGISwapChainFullScreenDesc();
	
		// 为当前窗口创建交换链
		HR(dxgiFactory2->CreateSwapChainForHwnd(owner->get_d3dDevice().Get(), windowInfo.window, &sd, &fd, nullptr, SwapChain1.GetAddressOf()));
		HR(SwapChain1.As(&SwapChain));
	}
	else
	{
		// 填充DXGI_SWAP_CHAIN_DESC用以描述交换链
		DXGI_SWAP_CHAIN_DESC sd = CreateDXGISwapChainDesc(windowInfo, owner->get_Msaa4xQuality());
		
		HR(dxgiFactory1->CreateSwapChain(owner->get_d3dDevice().Get(), &sd, SwapChain.GetAddressOf()));
	}

	// 可以禁止alt+enter全屏
	dxgiFactory1->MakeWindowAssociation(windowInfo.window, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

	DXGISetDebugObjectName(SwapChain.Get(), "SwapChain");
}
