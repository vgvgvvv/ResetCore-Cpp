//
// Created by 35207 on 2021/9/22 0022.
//

#pragma once
#include "D3D12RHI_API.h"
#include "Singleton.h"
#include "D3D12Utils.h"

class D3D12RHI_API D3D12RHI {

	DEFINE_SINGLETON(D3D12RHI)
public:
	void Init(D3D12WindowInfo windowInfo);
	void Uninit();

	DEFINE_GETTER(D3D12WindowInfo, windowInfo);

private:
	D3D12WindowInfo windowInfo;
};




