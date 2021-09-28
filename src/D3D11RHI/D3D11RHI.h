#pragma once
#include "Singleton.h"
#include <memory>
#include "D3D11Utils.h"
#include "D3D11RHI_API.h"

class D3D11RHI_API D3D11RHI
{
	DEFINE_SINGLETON(D3D11RHI);
public:
	void Init(D3D11WindowInfo windowInfo);
	void OnResize();
	void Uninit();

	DEFINE_GETTER(D3D11WindowInfo, windowInfo);
	
private:
	std::shared_ptr<class D3D11Device> device;
	D3D11WindowInfo windowInfo;
};