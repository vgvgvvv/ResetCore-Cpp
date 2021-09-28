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
	// 驱动类型数组
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// 特性等级数组
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
			// Direct3D 11.0 的API不承认D3D_FEATURE_LEVEL_11_1，所以我们需要尝试特性等级11.0以及以下的版本
			hr = D3D11CreateDevice(nullptr, d3dDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, d3dImmediateContext.GetAddressOf());
		}

		if (SUCCEEDED(hr))
			break;
	}

	RE_ASSERT_MSG(SUCCEEDED(hr), "D3D11CreateDevice Failed.");

	// 检测是否支持特性等级11.0或11.1
	if (featureLevel != D3D_FEATURE_LEVEL_11_0 && featureLevel != D3D_FEATURE_LEVEL_11_1)
	{
		RE_ASSERT_MSG(false, "Direct3D Feature Level 11 unsupported.");
	}

	// 检测 MSAA支持的质量等级
	d3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Msaa4xQuality);
	assert(Msaa4xQuality > 0);

	// 设置调试对象名
	D3D11SetDebugObjectName(d3dImmediateContext.Get(), "ImmediateContext");
}
