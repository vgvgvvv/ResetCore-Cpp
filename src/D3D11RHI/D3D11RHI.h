#pragma once
#include "Singleton.h"
#include <windows.h>
#include "D3D11RHI_API.h"

struct D3D11WindowInfo
{
	int width;
	int height;
	HINSTANCE windowInstance;
	HWND window;
};


class D3D11RHI_API D3D11RHI
{
	DEFINE_SINGLETON(D3D11RHI);
public:
	void Init(D3D11WindowInfo windowInfo);
	void Uninit();
	
};