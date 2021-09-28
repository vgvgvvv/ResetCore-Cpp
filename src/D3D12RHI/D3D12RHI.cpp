//
// Created by 35207 on 2021/9/22 0022.
//

#include "D3D12RHI.h"
#include "D3D12Utils.h"

void D3D12RHI::InitSingleton()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif
}

void D3D12RHI::Init(D3D12WindowInfo windowInfo)
{
}

void D3D12RHI::Uninit()
{
}
