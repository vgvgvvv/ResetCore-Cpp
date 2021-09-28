#pragma once
#include "D3D11Structs.h"
#include "Misc/GlobalContext.h"

namespace D3D11
{
	namespace Initializer
	{
		inline DXGI_SWAP_CHAIN_FULLSCREEN_DESC CreateDXGISwapChainFullScreenDesc()
		{
			DXGI_SWAP_CHAIN_FULLSCREEN_DESC fd;
			fd.RefreshRate.Numerator = 60;
			fd.RefreshRate.Denominator = 1;
			fd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			fd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			fd.Windowed = TRUE;
			return fd;
		}

		inline DXGI_SWAP_CHAIN_DESC CreateDXGISwapChainDesc(D3D11WindowInfo windowInfo, UINT msaaQuality)
		{
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferDesc.Width = windowInfo.width;
			sd.BufferDesc.Height = windowInfo.height;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			static auto enableMsaa = GlobalContext::Get().GetBoolValue("d3d11.enable4xMSAA", false);
			// 是否开启4倍多重采样？
			if (enableMsaa)
			{
				sd.SampleDesc.Count = 4;
				sd.SampleDesc.Quality = msaaQuality - 1;
			}
			else
			{
				sd.SampleDesc.Count = 1;
				sd.SampleDesc.Quality = 0;
			}
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;
			sd.OutputWindow = windowInfo.window;
			sd.Windowed = TRUE;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = 0;

			return sd;
		}

		inline DXGI_SWAP_CHAIN_DESC1 CreateDXGISwapChainDesc1(D3D11WindowInfo windowInfo, UINT msaaQuality)
		{
			DXGI_SWAP_CHAIN_DESC1 sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.Width = windowInfo.width;
			sd.Height = windowInfo.height;
			sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

			static auto enableMsaa = GlobalContext::Get().GetBoolValue("d3d11.enable4xMSAA", false);
			// 是否开启4倍多重采样？
			if (enableMsaa)
			{
				sd.SampleDesc.Count = 4;
				sd.SampleDesc.Quality = msaaQuality - 1;
			}
			else
			{
				sd.SampleDesc.Count = 1;
				sd.SampleDesc.Quality = 0;
			}
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = 0;

			return sd;
		}

		inline D3D11_TEXTURE2D_DESC CreateDepthStencilTextureDesc(D3D11WindowInfo windowInfo, UINT msaaQuality)
		{
			D3D11_TEXTURE2D_DESC depthStencilDesc;

			depthStencilDesc.Width = windowInfo.width;
			depthStencilDesc.Height = windowInfo.height;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

			static auto enableMsaa = GlobalContext::Get().GetBoolValue("d3d11.enable4xMSAA", false);
			// 要使用 4X MSAA? --需要给交换链设置MASS参数
			if (enableMsaa)
			{
				depthStencilDesc.SampleDesc.Count = 4;
				depthStencilDesc.SampleDesc.Quality = msaaQuality - 1;
			}
			else
			{
				depthStencilDesc.SampleDesc.Count = 1;
				depthStencilDesc.SampleDesc.Quality = 0;
			}



			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0;
			depthStencilDesc.MiscFlags = 0;

			return depthStencilDesc;
		}
	}
}
