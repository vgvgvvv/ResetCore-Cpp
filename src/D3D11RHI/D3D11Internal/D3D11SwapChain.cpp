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
	// �ͷ���Ⱦ��������õ��������Դ
	RenderTargetView.Reset();
	DepthStencilView.Reset();
	DepthStencilBuffer.Reset();

	// ���轻�����������´�����ȾĿ����ͼ
	ComPtr<ID3D11Texture2D> backBuffer;
	auto windowInfo = D3D11RHI::Get().get_windowInfo();
	HR(SwapChain->ResizeBuffers(1, windowInfo.width, windowInfo.height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	HR(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
	HR(owner->get_d3dDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, RenderTargetView.GetAddressOf()));

	// ���õ��Զ�����
	D3D11SetDebugObjectName(backBuffer.Get(), "BackBuffer[0]");

	backBuffer.Reset();

	D3D11_TEXTURE2D_DESC depthStencilDesc = CreateDepthStencilTextureDesc(windowInfo, owner->get_Msaa4xQuality());

	// ������Ȼ������Լ����ģ����ͼ
	HR(owner->get_d3dDevice()->CreateTexture2D(&depthStencilDesc, nullptr, DepthStencilBuffer.GetAddressOf()));
	HR(owner->get_d3dDevice()->CreateDepthStencilView(DepthStencilBuffer.Get(), nullptr, DepthStencilView.GetAddressOf()));

	// ����ȾĿ����ͼ�����/ģ�建������ϵ�����
	owner->get_d3dImmediateContext()->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());

	// �����ӿڱ任
	ScreenViewport.TopLeftX = 0;
	ScreenViewport.TopLeftY = 0;
	ScreenViewport.Width = static_cast<float>(windowInfo.width);
	ScreenViewport.Height = static_cast<float>(windowInfo.height);
	ScreenViewport.MinDepth = 0.0f;
	ScreenViewport.MaxDepth = 1.0f;

	owner->get_d3dImmediateContext()->RSSetViewports(1, &ScreenViewport);

	// ���õ��Զ�����
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
	ComPtr<IDXGIFactory1> dxgiFactory1 = nullptr;	// D3D11.0(����DXGI1.1)�Ľӿ���
	ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;	// D3D11.1(����DXGI1.2)���еĽӿ���

	// Ϊ����ȷ���� DXGI������������������Ҫ��ȡ���� D3D�豸 �� DXGI�������������������
	// "IDXGIFactory::CreateSwapChain: This function is being called with a device from a different IDXGIFactory."
	HR(owner->get_d3dDevice().As(&dxgiDevice));
	HR(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1.GetAddressOf())));

	// �鿴�ö����Ƿ����IDXGIFactory2�ӿ�
	hr = dxgiFactory1.As(&dxgiFactory2);

	auto windowInfo = D3D11RHI::Get().get_windowInfo();
	static auto enableMsaa = GlobalContext::Get().GetBoolValue("d3d11.enable4xMSAA", false);
	
	// �����������˵��֧��D3D11.1
	if (dxgiFactory2 != nullptr)
	{
		auto d3dDevice = owner->get_d3dDevice();
		auto d3dImmediateContext = owner->get_d3dImmediateContext();
		auto d3dDevice1 = owner->get_d3dDevice1();
		auto d3dImmediateContext1 = owner->get_d3dImmediateContext1();
		
		HR(d3dDevice.As(&d3dDevice1));
		HR(d3dImmediateContext.As(&d3dImmediateContext1));
		// �����ֽṹ����������������
		DXGI_SWAP_CHAIN_DESC1 sd = 
			CreateDXGISwapChainDesc1(windowInfo, owner->get_Msaa4xQuality());

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd = CreateDXGISwapChainFullScreenDesc();
	
		// Ϊ��ǰ���ڴ���������
		HR(dxgiFactory2->CreateSwapChainForHwnd(owner->get_d3dDevice().Get(), windowInfo.window, &sd, &fd, nullptr, SwapChain1.GetAddressOf()));
		HR(SwapChain1.As(&SwapChain));
	}
	else
	{
		// ���DXGI_SWAP_CHAIN_DESC��������������
		DXGI_SWAP_CHAIN_DESC sd = CreateDXGISwapChainDesc(windowInfo, owner->get_Msaa4xQuality());
		
		HR(dxgiFactory1->CreateSwapChain(owner->get_d3dDevice().Get(), &sd, SwapChain.GetAddressOf()));
	}

	// ���Խ�ֹalt+enterȫ��
	dxgiFactory1->MakeWindowAssociation(windowInfo.window, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);

	DXGISetDebugObjectName(SwapChain.Get(), "SwapChain");
}
