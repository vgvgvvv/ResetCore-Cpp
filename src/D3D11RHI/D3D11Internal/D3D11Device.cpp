#include "D3D11Device.h"

#include <cassert>

#include "CommonAssert.h"

void D3D11Device::Init()
{
	RE_LOG_INFO("D3D11", "InitDevice");
	CreateDevice();
	swapchain->Init(this);
	OnResize();
}

void D3D11Device::OnResize()
{
	assert(d3dImmediateContext);
	assert(d3dDevice);

	if (d3dDevice1 != nullptr)
	{
		assert(d3dImmediateContext1);
		assert(d3dDevice1);
	}
	swapchain->OnResize();
}

void D3D11Device::Uninit()
{
	RE_LOG_INFO("D3D11", "UninitDevice");
	swapchain->Uninit();
}

void D3D11Device::CreateDevice()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// ������������
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// ���Եȼ�����
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_FEATURE_LEVEL featureLevel;
	D3D_DRIVER_TYPE d3dDriverType;
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		d3dDriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, d3dDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, d3dImmediateContext.GetAddressOf());

		if (hr == E_INVALIDARG)
		{
			// Direct3D 11.0 ��API������D3D_FEATURE_LEVEL_11_1������������Ҫ�������Եȼ�11.0�Լ����µİ汾
			hr = D3D11CreateDevice(nullptr, d3dDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, d3dImmediateContext.GetAddressOf());
		}

		if (SUCCEEDED(hr))
			break;
	}

	RE_ASSERT_MSG(SUCCEEDED(hr), "D3D11CreateDevice Failed.");

	// ����Ƿ�֧�����Եȼ�11.0��11.1
	if (featureLevel != D3D_FEATURE_LEVEL_11_0 && featureLevel != D3D_FEATURE_LEVEL_11_1)
	{
		RE_ASSERT_MSG(false, "Direct3D Feature Level 11 unsupported.");
	}

	// ��� MSAA֧�ֵ������ȼ�
	d3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Msaa4xQuality);
	assert(Msaa4xQuality > 0);

	// ���õ��Զ�����
	D3D11SetDebugObjectName(d3dImmediateContext.Get(), "ImmediateContext");
}
